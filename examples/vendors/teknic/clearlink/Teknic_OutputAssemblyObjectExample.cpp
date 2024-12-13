#include <chrono>
#include <cstdint>
#include <memory>
#include <optional>
#include <stdexcept>
#include <thread>
#include <optional>

#include <EIPScanner/cip/Types.h>
#include <EIPScanner/utils/Logger.h>
#include <EIPScanner/vendor/teknic/clearlink/ConfigAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/InputAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/OutputAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/assembly/config/MotorConfigData.h>
#include <EIPScanner/vendor/teknic/clearlink/assembly/input/MotorInputData.h>
#include <EIPScanner/vendor/teknic/clearlink/assembly/output/MotorOutputData.h>

/* All of the functions here are based off of the Teknic Documentation.
		Unfortunately most of that is rough around the edges.

	Using the Step & Direction Motor Input Object reference, the requirements could be deduced:
		https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=41

	The teknic clearlink examples also provide Ladder Logic that steps through the process:
		https://teknic.com/downloads/

	------------------------------------------------------
	
	In brief, there are two types of movements:
		1. Positional Move
		2. Velocity Move

	For both movements
		1. Any outstanding faults need to be cleared
			* There are two types of faults that can occur:
				1. Motor Faults/Alerts
				2. Motor Shutdowns 

		2. The motor must be "Enabled"
			* Command == EIP_OUTPUT->setOutputFlag(SDMotorOutputObject::OutputFlag::Enable, true)
			* NOTE: When the Brake Pin has been set, enabling the motor will also set the brake output

		3. The "Load<Type>Move" bit must be UN-set
			* Positional == EIP_OUTPUT->setOutputFlag(SDMotorOutputObject::OutputFlag::LoadPositionalMove, false)
			* Velocity == EIP_OUTPUT->setOutputFlag(SDMotorOutputObject::OutputFlag::LoadVelocityMove, false)
		
		4. The target must be loaded into the appropriate register
			* Positional == EIP_OUTPUT->setMoveDistance()
			* Velocity == EIP_OUTPUT->setJogVelocity()
		
		5. The "Load<Type>Move" bit must be set 
			* See step 3 for the correct flags

		6. The ACK for the "Load<Type>Move" bit must be read from the Clearlink
			* Command == EIP_INPUT->isInState(SDMotorInputObject::InputState::Load<Type>MoveAck)

		7. The "Load<Type>Move" bit must be UN-set
			* See step 3 for the correct flags

		8. The motor should be UN-Enabled (if motion has stopped)
			* See step 2 for the correct flags
			* NOTE: When the Brake Pin has been set, UN-enabling the motor will also UN-set the brake output
			* NOTE 2: If a non-zero velocity move has been commanded, the motor should stay enabled 
*/


using namespace eipScanner::vendor::teknic;
using eipScanner::vendor::teknic::clearlink::assembly::config::MotorConfigData;
using eipScanner::vendor::teknic::clearlink::assembly::input::MotorInputData;
using eipScanner::vendor::teknic::clearlink::assembly::output::MotorOutputData;

using eipScanner::cip::CipDint;
using eipScanner::cip::CipUdint;

enum class MoveInstructionState
{
	COMPLETED,
	IN_PROGRESS,
	FAULTED
};

std::string instructionToString(MoveInstructionState state)
{
	switch (state)
	{
		case MoveInstructionState::COMPLETED:
			return "COMPLETED";
		case MoveInstructionState::IN_PROGRESS:
			return "IN_PROGRESS";
		case MoveInstructionState::FAULTED:	
			return "FAULTED";
		default:
			return "UNKNOWN";
	}
};

struct ClearlinkIO {
  clearlink::ConfigAssemblyObject config;
  clearlink::InputAssemblyObject input;
  clearlink::OutputAssemblyObject output;
};

// Taken from spec sheet:
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=46
const eipScanner::cip::CipUdint MAX_STEPS_PER_SECOND = 500000;
const eipScanner::cip::CipUdint MAX_ACCELERATION_STEPS_PER_SECOND_SQUARED =
    500000;

clearlink::assembly::config::MotorConfigData getMotorConfig(clearlink::ConfigAssemblyObject clearlinkConfig,
                                                            uint8_t motorConnectorId)
{
	switch (motorConnectorId)
	{
	case 0:
		return clearlinkConfig.getMotor0ConfigData();
	case 1:
		return clearlinkConfig.getMotor1ConfigData();
	case 2:
		return clearlinkConfig.getMotor2ConfigData();
	case 3:
		return clearlinkConfig.getMotor3ConfigData();
	default:
		throw std::runtime_error("Unknown motor config connector ID " + std::to_string(motorConnectorId));
	}
}

void setMotorConfig(clearlink::ConfigAssemblyObject &clearlinkConfig,
                    uint8_t motorConnectorId,
                    clearlink::assembly::config::MotorConfigData motorConfigData)
{
	switch (motorConnectorId)
	{
	case 0:
		clearlinkConfig.setMotor0ConfigData(motorConfigData);
		break;
	case 1:
		clearlinkConfig.setMotor1ConfigData(motorConfigData);
		break;
	case 2:
		clearlinkConfig.setMotor2ConfigData(motorConfigData);
		break;
	case 3:
		clearlinkConfig.setMotor3ConfigData(motorConfigData);
		break;
	default:
		throw std::runtime_error("Unknown motor config connector ID " + std::to_string(motorConnectorId));
	}
}

clearlink::assembly::input::MotorInputData getMotorInput(clearlink::InputAssemblyObject clearlinkInput,
                                                         uint8_t motorConnectorId)
{
	switch (motorConnectorId)
	{
	case 0:
		return clearlinkInput.getMotor0InputData();
	case 1:
		return clearlinkInput.getMotor1InputData();
	case 2:
		return clearlinkInput.getMotor2InputData();
	case 3:
		return clearlinkInput.getMotor3InputData();
	default:
		throw std::runtime_error("Unknown motor input connector ID " + std::to_string(motorConnectorId));
	}
}

void setMotorInput(clearlink::InputAssemblyObject &clearlinkInput,
                   uint8_t motorConnectorId,
                   clearlink::assembly::input::MotorInputData motorInputData)
{
	switch (motorConnectorId)
	{
	case 0:
		clearlinkInput.setMotor0InputData(motorInputData);
		break;
	case 1:
		clearlinkInput.setMotor1InputData(motorInputData);
		break;
	case 2:
		clearlinkInput.setMotor2InputData(motorInputData);
		break;
	case 3:
		clearlinkInput.setMotor3InputData(motorInputData);
		break;
	default:
		throw std::runtime_error("Unknown motor input connector ID " + std::to_string(motorConnectorId));
	}
}

clearlink::assembly::output::MotorOutputData getMotorOutput(clearlink::OutputAssemblyObject clearlinkOutput,
                                                            uint8_t motorConnectorId)
{
	switch (motorConnectorId)
	{
	case 0:
		return clearlinkOutput.getMotor0OutputData();
	case 1:
		return clearlinkOutput.getMotor1OutputData();
	case 2:
		return clearlinkOutput.getMotor2OutputData();
	case 3:
		return clearlinkOutput.getMotor3OutputData();
	default:
		throw std::runtime_error("Unknown motor output connector ID " + std::to_string(motorConnectorId));
	}
}

void setMotorOutput(clearlink::OutputAssemblyObject &clearlinkOutput,
                    uint8_t motorConnectorId,
                    clearlink::assembly::output::MotorOutputData motorOutputData)
{
	switch (motorConnectorId)
	{
	case 0:
		clearlinkOutput.setMotor0OutputData(motorOutputData);
		break;
	case 1:
		clearlinkOutput.setMotor1OutputData(motorOutputData);
		break;
	case 2:
		clearlinkOutput.setMotor2OutputData(motorOutputData);
		break;
	case 3:
		clearlinkOutput.setMotor3OutputData(motorOutputData);
		break;
	default:
		throw std::runtime_error("Unknown motor output connector ID " + std::to_string(motorConnectorId));
	}
}

// ------------------------------
// initialize the object assembly wrappers
// -------------
ClearlinkIO createClearlinkIOObjects(std::string ipAddress, int port)
{
	// EthernetIP variables
	const auto sessionInfoPtr = std::make_shared<eipScanner::SessionInfo>(ipAddress, port);

	// need to make sure that the EPath is padded in 8-bit segments or the MessageRouter SET_ATTRIBUTE_SINGLE request will fail
	const auto messageRouterPtr = std::make_shared<eipScanner::MessageRouter>(true);

	auto clearlinkConfiguration = clearlink::ConfigAssemblyObject(sessionInfoPtr, messageRouterPtr);
	auto clearlinkInput = clearlink::InputAssemblyObject(sessionInfoPtr, messageRouterPtr);
	auto clearlinkOutput = clearlink::OutputAssemblyObject(sessionInfoPtr, messageRouterPtr);

	return {clearlinkConfiguration, clearlinkInput, clearlinkOutput};
}

MotorConfigData initializeMotorConfigData(double brakeControlPinId,
                                          double positiveLimitPinId,
                                          double negativeLimitPinId,
                                          double homingSensorPinId,
                                          CipDint positiveSoftLimit,
                                          CipDint negativeSoftLimit)
{
	MotorConfigData motorConfigData;

	motorConfigData.setBrakeOutputConnector(brakeControlPinId);
	motorConfigData.setPositiveLimitConnector(positiveLimitPinId);
	motorConfigData.setNegativeLimitConnector(negativeLimitPinId);
	motorConfigData.setHomeSensorConnector(homingSensorPinId);

	motorConfigData.setSoftLimitPosition1(positiveSoftLimit);
	motorConfigData.setSoftLimitPosition2(negativeSoftLimit);

	motorConfigData.setConfigRegisterFlag(MotorConfigData::ConfigFlag::HomingEnable, true);
	motorConfigData.setConfigRegisterFlag(MotorConfigData::ConfigFlag::HLFBInversion, true);
	motorConfigData.setConfigRegisterFlag(MotorConfigData::ConfigFlag::SoftwareLimitEnable, false);

	return motorConfigData;
}

MotorOutputData initializeMotorOutputdata()
{
	MotorOutputData motorOutputData;

	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::Enable, false);
	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::AbsoluteMove, false);
	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::HomingMove, false);
	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::LoadPositionMove, false);
	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::LoadVelocityMove, false);
	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::SoftwareEStop, false);
	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::ClearAlerts, false);
	motorOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::ClearMotorFault, false);

	return motorOutputData;
}

bool faultsCleared(MotorInputData motorInputData)
{
	return !motorInputData.hasMotorStatus(MotorInputData::MotorInFault) &&
	       !motorInputData.hasMotorStatus(MotorInputData::ShutdownsPresent);
}

MotorOutputData createClearFaultsOutput(MotorInputData motorInputData, MotorOutputData previousOutputData)
{

	/*
   * if the motor is in fault, set the ClearFault bit
   * if the motor is NOT in fault, UNset the ClearFault bit
   *
   * toggling the ENABLE bit can clear E-Stop issues as well
   */
	if (motorInputData.hasMotorStatus(MotorInputData::MotorInFault))
	{

		bool clearFaultsSet = previousOutputData.hasFlagSet(MotorOutputData::ClearMotorFault);
		bool enableSet = previousOutputData.hasFlagSet(MotorOutputData::Enable);

		previousOutputData.setOutputRegisterFlag(MotorOutputData::ClearMotorFault, !clearFaultsSet);
		previousOutputData.setOutputRegisterFlag(MotorOutputData::Enable, !enableSet);
	}

	/*
   * If the motor has a shutdown present (AND the motor is NOT in fault), set
   * the ClearShutdown bit If the motor does NOT have a shutdown present, UNset
   * the ClearShutdown bit
   */
	if (motorInputData.hasMotorStatus(MotorInputData::ShutdownsPresent))
	{
		bool clearAlertsSet = previousOutputData.hasFlagSet(MotorOutputData::ClearAlerts);

		// need to toggle the bit
		previousOutputData.setOutputRegisterFlag(MotorOutputData::ClearAlerts, !clearAlertsSet);
	}

	return previousOutputData;
}

MotorOutputData createMoveCommandOutput(MotorOutputData previousOutputData,
                                        MotorOutputData::OutputFlag loadMoveFlag,
                                        eipScanner::cip::CipUdint maxVelocitySteps,
                                        eipScanner::cip::CipUdint maxAccelerationSteps)
{
	bool moveAlreadySet = previousOutputData.hasFlagSet(loadMoveFlag);

	previousOutputData.setOutputRegisterFlag(loadMoveFlag, !moveAlreadySet);

	eipScanner::cip::CipUdint maxStepsPerSecond =
		maxVelocitySteps > MAX_STEPS_PER_SECOND ? MAX_STEPS_PER_SECOND : maxVelocitySteps;
	eipScanner::cip::CipUdint maxStepsPerSecondSquared =
		maxAccelerationSteps > MAX_ACCELERATION_STEPS_PER_SECOND_SQUARED ? MAX_ACCELERATION_STEPS_PER_SECOND_SQUARED
																		 : maxAccelerationSteps;

	previousOutputData.setVelocityLimit(maxStepsPerSecond);
	previousOutputData.setAccelerationLimit(maxStepsPerSecondSquared);
	previousOutputData.setDecelerationLimit(maxStepsPerSecondSquared);

	previousOutputData.setOutputRegisterFlag(MotorOutputData::Enable, true);
	previousOutputData.setOutputRegisterFlag(MotorOutputData::HomingMove, false);

	// reset unused flags
	previousOutputData.setOutputRegisterFlag(MotorOutputData::SoftwareEStop, false);
	previousOutputData.setOutputRegisterFlag(MotorOutputData::ClearAlerts, false);
	previousOutputData.setOutputRegisterFlag(MotorOutputData::ClearMotorFault, false);

	// TODO(jan): Decide whether there should be additional logic to handle the case where the motor is already moving
	//	- Previously this was handled by setting the Load flag to false, sending the command, and then setting the move to true

	eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
		<< "Motor is moving "
		<< (loadMoveFlag == MotorOutputData::OutputFlag::LoadPositionMove ? "POSITIONALLY" : "VELOCITILY")
		<< " and bit flag is: " << (moveAlreadySet ? "true" : "false");

	return previousOutputData;
}

MotorOutputData createPositionMoveOutput(MotorOutputData previousOutputData,
                                         int positionSetPoint,
                                         eipScanner::cip::CipUdint maxVelocitySteps,
                                         eipScanner::cip::CipUdint maxAccelerationSteps,
                                         bool absoluteMove)
{

	eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO) << "Motor is ready to POSITIONAL move";

	previousOutputData.setMoveDistance(positionSetPoint);
	previousOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::AbsoluteMove, absoluteMove);
	previousOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::LoadVelocityMove, false);

	return createMoveCommandOutput(
		previousOutputData, MotorOutputData::OutputFlag::LoadPositionMove, maxVelocitySteps, maxAccelerationSteps);
}

MotorOutputData createReachedPositionOutput(MotorInputData /* motorInputData */, MotorOutputData previousOutputData)
{
	eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
		<< "Motor finished moving to POSITION, un-latching LoadPositionMove";

	previousOutputData.setOutputRegisterFlag(MotorOutputData::LoadPositionMove, false);
	previousOutputData.setOutputRegisterFlag(MotorOutputData::Enable, false);

	return previousOutputData;
}

std::pair<MoveInstructionState, std::optional<MotorOutputData>>
moveToMotorPositionNonBlocking(MotorInputData motorInputData,
                               MotorOutputData previousOutputData,
                               int positionSetPoint,
                               eipScanner::cip::CipUdint maxVelocitySteps,
                               eipScanner::cip::CipUdint maxAccelerationSteps,
                               bool absoluteMove)
{
	int32_t previouslySetTargetPosition = previousOutputData.getMoveDistance();
	int32_t currentMotorPosition = motorInputData.getCommandedPosition();

	bool positionMoveCommanded = motorInputData.hasMotorStatus(MotorInputData::PositionalMove);
	bool absolutePositionCommanded = previousOutputData.hasFlagSet(MotorOutputData::AbsoluteMove);
	bool positionAlreadySet = positionSetPoint == previouslySetTargetPosition && positionMoveCommanded &&
	                          absoluteMove == absolutePositionCommanded;

	bool motorInMotion = motorInputData.hasMotorStatus(MotorInputData::StepsActive);

	// set the new position if:
	// 1. The motor is not currently at the desired position
	// 2. The motor is not currently moving to the desired velocity

	if (positionAlreadySet && motorInputData.hasMotorStatus(MotorInputData::AtTargetPosition))
	{
		return {MoveInstructionState::COMPLETED, createReachedPositionOutput(motorInputData, previousOutputData)};
	}

	if (positionAlreadySet && positionSetPoint == currentMotorPosition && !motorInMotion)
	{
		// Move has already been completed
		return {MoveInstructionState::COMPLETED, std::nullopt};
	}

	if (positionAlreadySet && motorInputData.hasMotorStatus(MotorInputData::LoadPositionMoveAck))
	{
		// The move is currently happening
		return {MoveInstructionState::IN_PROGRESS, std::nullopt};
	}

	if (!faultsCleared(motorInputData))
	{
		return {MoveInstructionState::FAULTED, createClearFaultsOutput(motorInputData, previousOutputData)};
	}

	return {MoveInstructionState::IN_PROGRESS,
	        createPositionMoveOutput(
				previousOutputData, positionSetPoint, maxVelocitySteps, maxAccelerationSteps, absoluteMove)};
}

MotorOutputData createVelocityMoveOutput(MotorOutputData previousOutputData,
                                         int velocitySetPoint,
                                         eipScanner::cip::CipUdint maxAccelerationSteps)
{
	eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO) << "Motor is ready to VELOCITY move";

	previousOutputData.setJogVelocity(velocitySetPoint);
	previousOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::LoadPositionMove, false);

	return createMoveCommandOutput(previousOutputData,
	                               MotorOutputData::OutputFlag::LoadVelocityMove,
	                               /* maxVelocity */ 0,
	                               maxAccelerationSteps);
}

MotorOutputData createReachedVelocityOutput(MotorInputData motorInputData, MotorOutputData previousOutputData)
{

	eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
		<< "Motor finished moving at VELOCITY, un-latching LoadVelocityMove";

	previousOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::LoadVelocityMove, false);

	// If the velocity has been set to 0, then disable the motor
	if (motorInputData.getCommandedVelocity() == 0)
	{
		previousOutputData.setOutputRegisterFlag(MotorOutputData::OutputFlag::Enable, false);
	}

	return previousOutputData;
}

std::pair<MoveInstructionState, std::optional<MotorOutputData>>
moveToMotorVelocityNonBlocking(MotorInputData motorInputData,
                               MotorOutputData previousOutputData,
                               int velocitySetPoint,
                               CipUdint maxAccelerationSteps)
{
	int32_t previouslySetMotorVelocity = previousOutputData.getJogVelocity();

	int32_t currentMotorVelocity = motorInputData.getCommandedVelocity();

	bool motorInMotion = motorInputData.hasMotorStatus(MotorInputData::MotorStatus::StepsActive);

	// set the new velocity if:
	// 1. The motor is not currently spinning at the desired velocity
	// 2. The motor is not currently accelerating/decelerating to the desired velocity
	// 3. The motor is not currently set to the desired velocity

	bool velocityMoveCommanded = !motorInputData.hasMotorStatus(MotorInputData::MotorStatus::PositionalMove);
	bool velocityAlreadySet = velocitySetPoint == previouslySetMotorVelocity && velocityMoveCommanded;

	if (velocityAlreadySet && motorInputData.hasMotorStatus(MotorInputData::MotorStatus::LoadVelocityMoveAck) &&
	    motorInputData.hasMotorStatus(MotorInputData::MotorStatus::AtVelocity))
	{
		return {MoveInstructionState::IN_PROGRESS, createReachedVelocityOutput(motorInputData, previousOutputData)};
	}

	if (velocityAlreadySet && velocitySetPoint == currentMotorVelocity)
	{
		// Move has already been completed
		return {MoveInstructionState::COMPLETED, std::nullopt};
	}

	if (velocityAlreadySet && motorInMotion)
	{
		return {MoveInstructionState::IN_PROGRESS, std::nullopt};
	}

	if (!faultsCleared(motorInputData))
	{
		return {MoveInstructionState::FAULTED, createClearFaultsOutput(motorInputData, previousOutputData)};
	}

	return {MoveInstructionState::IN_PROGRESS,
	        createVelocityMoveOutput(previousOutputData, velocitySetPoint, maxAccelerationSteps)};
}

int main(int argc, char *argv[]) {

  int32_t inputPositionalSteps = 1000;
  bool isAbsoluteMove = false;

  if (argc > 1) {
    inputPositionalSteps = std::stoi(argv[1]);
  }

  if (argc > 2) {
    isAbsoluteMove = std::stoi(argv[2]);
  }

  eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
      << "Commanding move with " << inputPositionalSteps << " as absolute move "
      << (isAbsoluteMove ? "true" : "false");

  // Get the clearlinkIO (given a variable IP address and the default
  // Ethernet/IP port)
  ClearlinkIO clearlinkRepresentation =
      createClearlinkIOObjects("192.168.1.71", 0xAF12);

  for (uint8_t connectorId = 0; connectorId < 4; ++connectorId) {
    auto motorConfig = initializeMotorConfigData(-1, -1, -1, -1, 0, 0);
		setMotorConfig(clearlinkRepresentation.config, connectorId, motorConfig);
  }

  clearlinkRepresentation.config.setAssembly();


  uint8_t motorConnector = 0;
	auto motorOutput = getMotorOutput(clearlinkRepresentation.output, motorConnector);
	auto motorInput = getMotorInput(clearlinkRepresentation.input, motorConnector);

  // perform a move
  MoveInstructionState movementState = MoveInstructionState::COMPLETED;
	std::optional<MotorOutputData> nextMotorOutput;

  eipScanner::cip::CipUdint maxVelocitySteps = 5000;
  eipScanner::cip::CipUdint maxAccelerationSteps = 10000;
  do {
    std::tie(movementState, nextMotorOutput) = moveToMotorPositionNonBlocking(
        motorInput, motorOutput, inputPositionalSteps, maxVelocitySteps,
        maxAccelerationSteps, isAbsoluteMove);

		if (nextMotorOutput.has_value()) {
			motorOutput = nextMotorOutput.value();
			setMotorOutput(clearlinkRepresentation.output, motorConnector, motorOutput);
    	clearlinkRepresentation.output.setAssembly();
		}

    std::this_thread::sleep_for(std::chrono::milliseconds(250));

		clearlinkRepresentation.input.getAssembly();

		motorInput = getMotorInput(clearlinkRepresentation.input, motorConnector);
		// eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
		// 		<< "Reading input with:" 
		// 		<< "  Curr Pos: " << motorInput.getCommandedPosition()
		// 		<< "  vel: " << motorInput.getCommandedVelocity()
		// 		<< "  targetPos: " << motorInput.getTargetPosition()
		// 		<< "  targetVel: " << motorInput.getTargetVelocity()
		// 		<< "  status: " << motorInput.getMotorStatus();

		// eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
		// 		<< "Movement State == " << instructionToString(movementState);

  } while (movementState != MoveInstructionState::COMPLETED);

	// Starting Status 1 = 562186 		== 0b10001001110000001010
	// 		StepsActive  			= True
  //    Enabled           = True
  //    Positional Move   = True
  //    HLFB_On           = True
  //    PositionMoveAck   = True


	// Finished Status 1 = 545793 		== 0b10000101010000000001
  // 		AtTargetPosition  = True
  //    Enabled           = True
  //    Positional Move   = True
  //    HLFB_On           = True
  //    PositionMoveAck   = True
	// Finished Status 2 = 21505			== 0b00000101010000000001
	// 		AtTargetPosition  = True
  //    Enabled           = True
  //    Positional Move   = True
  //    HLFB_On           = True    
  // Final loop status = 4096				== 0b00000001000000000000
	// 		HLFB_On = True
}


/*
enum MotorStatus {
    AtTargetPosition = 0,
    StepsActive = 1,
    AtVelocity = 2,
    MoveDirection = 3,
    InPositiveLimit = 4,
    InNegativeLimit = 5,
    InEStopSensor = 6,
    InHomeSensor = 7,
    Homing = 8,
    MotorInFault = 9,
    Enabled = 10,
    OutsideSoftLimits = 11,
    PositionalMove = 12,
    HasHomed = 13,
    HLFB_On = 14,
    HasTorqueMeasurement = 15,
    ReadyToHome = 16,
    ShutdownsPresent = 17,
    AddToPositionAck = 18,
    LoadPositionMoveAck = 19,
    LoadVelocityMoveAck = 20,
    ClearMotorFaultAck = 21,
    NUM_STATES = 22
    // 22 - 31 are reserved
  };
*/