#include <chrono>
#include <memory>
#include <stdexcept>
#include <thread>

#include "EIPScanner/utils/Logger.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/MotorConfigData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/MotorInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/MotorOutputData.h"
#include <EIPScanner/cip/Types.h>
#include <EIPScanner/vendor/teknic/clearlink/ConfigAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/InputAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/OutputAssemblyObject.h>

using namespace eipScanner::vendor::teknic;
using eipScanner::vendor::teknic::clearlink::assembly::config::MotorConfigData;
using eipScanner::vendor::teknic::clearlink::assembly::input::MotorInputData;
using eipScanner::vendor::teknic::clearlink::assembly::output::MotorOutputData;

using eipScanner::cip::CipDint;
using eipScanner::cip::CipUdint;

// Taken from spec sheet:
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=46
const eipScanner::cip::CipUdint MAX_STEPS_PER_SECOND = 500000;
const eipScanner::cip::CipUdint MAX_ACCELERATION_STEPS_PER_SECOND_SQUARED =
    500000;

enum class MoveInstructionState { COMPLETED, IN_PROGRESS, FAULTED };

struct ClearlinkIO {
  std::shared_ptr<clearlink::ConfigAssemblyObject> configPtr;
  std::shared_ptr<clearlink::InputAssemblyObject> inputPtr;
  std::shared_ptr<clearlink::OutputAssemblyObject> outputPtr;
};

clearlink::assembly::config::MotorConfigData getMotorConfig(
    std::shared_ptr<clearlink::ConfigAssemblyObject> clearlinkConfigPtr,
    uint8_t motorConnectorId) {
  switch (motorConnectorId) {
  case 0:
    return clearlinkConfigPtr->getMotor0ConfigData();
  case 1:
    return clearlinkConfigPtr->getMotor1ConfigData();
  case 2:
    return clearlinkConfigPtr->getMotor2ConfigData();
  case 3:
    return clearlinkConfigPtr->getMotor3ConfigData();
  default:
    throw std::runtime_error("Unknown motor config connector ID " +
                             std::to_string(motorConnectorId));
  }
}

void setMotorConfig(
    std::shared_ptr<clearlink::ConfigAssemblyObject> clearlinkConfigPtr,
    uint8_t motorConnectorId,
    clearlink::assembly::config::MotorConfigData motorConfigData) {
  switch (motorConnectorId) {
  case 0:
    clearlinkConfigPtr->setMotor0ConfigData(motorConfigData);
    break;
  case 1:
    clearlinkConfigPtr->setMotor1ConfigData(motorConfigData);
    break;
  case 2:
    clearlinkConfigPtr->setMotor2ConfigData(motorConfigData);
    break;
  case 3:
    clearlinkConfigPtr->setMotor3ConfigData(motorConfigData);
    break;
  default:
    throw std::runtime_error("Unknown motor config connector ID " +
                             std::to_string(motorConnectorId));
  }
}

clearlink::assembly::input::MotorInputData
getMotorInput(std::shared_ptr<clearlink::InputAssemblyObject> clearlinkInputPtr,
              uint8_t motorConnectorId) {
  switch (motorConnectorId) {
  case 0:
    return clearlinkInputPtr->getMotor0InputData();
  case 1:
    return clearlinkInputPtr->getMotor1InputData();
  case 2:
    return clearlinkInputPtr->getMotor2InputData();
  case 3:
    return clearlinkInputPtr->getMotor3InputData();
  default:
    throw std::runtime_error("Unknown motor input connector ID " +
                             std::to_string(motorConnectorId));
  }
}

void setMotorInput(
    std::shared_ptr<clearlink::InputAssemblyObject> clearlinkInputPtr,
    uint8_t motorConnectorId,
    clearlink::assembly::input::MotorInputData motorInputData) {
  switch (motorConnectorId) {
  case 0:
    clearlinkInputPtr->setMotor0InputData(motorInputData);
    break;
  case 1:
    clearlinkInputPtr->setMotor1InputData(motorInputData);
    break;
  case 2:
    clearlinkInputPtr->setMotor2InputData(motorInputData);
    break;
  case 3:
    clearlinkInputPtr->setMotor3InputData(motorInputData);
    break;
  default:
    throw std::runtime_error("Unknown motor input connector ID " +
                             std::to_string(motorConnectorId));
  }
}

clearlink::assembly::output::MotorOutputData getMotorOutput(
    std::shared_ptr<clearlink::OutputAssemblyObject> clearlinkOutputPtr,
    uint8_t motorConnectorId) {
  switch (motorConnectorId) {
  case 0:
    return clearlinkOutputPtr->getMotor0OutputData();
  case 1:
    return clearlinkOutputPtr->getMotor1OutputData();
  case 2:
    return clearlinkOutputPtr->getMotor2OutputData();
  case 3:
    return clearlinkOutputPtr->getMotor3OutputData();
  default:
    throw std::runtime_error("Unknown motor output connector ID " +
                             std::to_string(motorConnectorId));
  }
}

void setMotorOutput(
    std::shared_ptr<clearlink::OutputAssemblyObject> clearlinkOutputPtr,
    uint8_t motorConnectorId,
    clearlink::assembly::output::MotorOutputData motorOutputData) {
  switch (motorConnectorId) {
  case 0:
    clearlinkOutputPtr->setMotor0OutputData(motorOutputData);
    break;
  case 1:
    clearlinkOutputPtr->setMotor1OutputData(motorOutputData);
    break;
  case 2:
    clearlinkOutputPtr->setMotor2OutputData(motorOutputData);
    break;
  case 3:
    clearlinkOutputPtr->setMotor3OutputData(motorOutputData);
    break;
  default:
    throw std::runtime_error("Unknown motor output connector ID " +
                             std::to_string(motorConnectorId));
  }
}

// ------------------------------
// initialize the object assembly wrappers
// -------------
ClearlinkIO createClearlinkIOObject(std::string clearlinkIpAddress,
                                    uint32_t clearlinkPort) {
  // EthernetIP variables
  // eipScanner::utils::Logger::setLogLevel(eipScanner::utils::LogLevel::INFO);
  const auto sessionInfoPtr = std::make_shared<eipScanner::SessionInfo>(
      clearlinkIpAddress, clearlinkPort);

  // need to make sure that the EPath is padded in 8-bit segments or the
  // SET_ATTRIBUTE_SINGLE request will fail
  const auto messageRouterPtr =
      std::make_shared<eipScanner::MessageRouter>(true);

  auto clearlinkConfiguration =
      clearlink::ConfigAssemblyObject(sessionInfoPtr, messageRouterPtr);
  auto clearlinkInput =
      clearlink::InputAssemblyObject(sessionInfoPtr, messageRouterPtr);
  auto clearlinkOutput =
      clearlink::OutputAssemblyObject(sessionInfoPtr, messageRouterPtr);

  // read the current values on the Clearlink
  clearlinkConfiguration.getAssembly();
  clearlinkInput.getAssembly();
  clearlinkOutput.getAssembly();

  return {
      std::make_shared<clearlink::ConfigAssemblyObject>(clearlinkConfiguration),
      std::make_shared<clearlink::InputAssemblyObject>(clearlinkInput),
      std::make_shared<clearlink::OutputAssemblyObject>(clearlinkOutput)};
}

void initializeMotorConfiguration(
    std::shared_ptr<clearlink::ConfigAssemblyObject> clearlinkConfigPtr,
    uint8_t motorConnectorId, double brakeControlPinId,
    double positiveLimitPinId, double negativeLimitPinId,
    double homingSensorPinId, CipDint positiveSoftLimit,
    CipDint negativeSoftLimit) {

  // read from the correct motor id
  auto motorConfig = getMotorConfig(clearlinkConfigPtr, motorConnectorId);

  motorConfig.setBrakeOutputConnector(brakeControlPinId);
  motorConfig.setPositiveLimitConnector(positiveLimitPinId);
  motorConfig.setNegativeLimitConnector(negativeLimitPinId);
  motorConfig.setHomeSensorConnector(homingSensorPinId);

  motorConfig.setSoftLimitPosition1(positiveSoftLimit);
  motorConfig.setSoftLimitPosition2(negativeSoftLimit);

  motorConfig.setConfigRegisterFlag(MotorConfigData::ConfigFlag::HomingEnable,
                                    true);
  motorConfig.setConfigRegisterFlag(MotorConfigData::ConfigFlag::HLFBInversion,
                                    true);
  motorConfig.setConfigRegisterFlag(
      MotorConfigData::ConfigFlag::SoftwareLimitEnable, false);

  // Write it back to the correct motor ID
  setMotorConfig(clearlinkConfigPtr, motorConnectorId, motorConfig);
}

bool faultsClearedSuccessfully(
    std::shared_ptr<clearlink::InputAssemblyObject> clearlinkInputObjectPtr,
    std::shared_ptr<clearlink::OutputAssemblyObject> clearlinkOutputObjectPtr,
    uint8_t motorConnectorId) {

  MotorInputData motorInputData =
      getMotorInput(clearlinkInputObjectPtr, motorConnectorId);

  MotorOutputData motorOutputData =
      getMotorOutput(clearlinkOutputObjectPtr, motorConnectorId);

  if (!motorInputData.hasMotorStatus(MotorInputData::MotorInFault) &&
      !motorInputData.hasMotorStatus(MotorInputData::ShutdownsPresent)) {
    return true;
  }

  /*
   * if the motor is in fault, set the ClearFault bit
   * if the motor is NOT in fault, UNset the ClearFault bit
   *
   * toggling the ENABLE bit can clear E-Stop issues as well
   */
  if (motorInputData.hasMotorStatus(MotorInputData::MotorInFault)) {

    bool clearFaultsSet =
        motorOutputData.hasFlagSet(MotorOutputData::ClearMotorFault);
    bool enableSet = motorOutputData.hasFlagSet(MotorOutputData::Enable);

    motorOutputData.setOutputRegisterFlag(MotorOutputData::ClearMotorFault,
                                          !clearFaultsSet);
    motorOutputData.setOutputRegisterFlag(MotorOutputData::Enable, !enableSet);

    // write that back to the pointer
    setMotorOutput(clearlinkOutputObjectPtr, motorConnectorId, motorOutputData);
  }

  /*
   * If the motor has a shutdown present (AND the motor is NOT in fault), set
   * the ClearShutdown bit If the motor does NOT have a shutdown present, UNset
   * the ClearShutdown bit
   */
  if (motorInputData.hasMotorStatus(MotorInputData::ShutdownsPresent)) {
    bool clearAlertsSet =
        motorOutputData.hasFlagSet(MotorOutputData::ClearAlerts);

    // need to toggle the bit
    motorOutputData.setOutputRegisterFlag(MotorOutputData::ClearAlerts,
                                          !clearAlertsSet);

    setMotorOutput(clearlinkOutputObjectPtr, motorConnectorId, motorOutputData);
  }

  // actually write the output pointer
  clearlinkOutputObjectPtr->setAssembly();
  return false;
}

void loadMotorMoveCommand(
    std::shared_ptr<clearlink::OutputAssemblyObject> clearlinkOutputObjectPtr,
    uint8_t motorConnectorId, MotorOutputData::OutputFlag loadMoveFlag,
    eipScanner::cip::CipUdint maxVelocitySteps,
    eipScanner::cip::CipUdint maxAccelerationSteps) {
  MotorOutputData motorOutputData =
      getMotorOutput(clearlinkOutputObjectPtr, motorConnectorId);

  bool moveAlreadySet = motorOutputData.hasFlagSet(loadMoveFlag);

  motorOutputData.setOutputRegisterFlag(loadMoveFlag, !moveAlreadySet);

  eipScanner::cip::CipUdint maxStepsPerSecond =
      maxVelocitySteps > MAX_STEPS_PER_SECOND ? MAX_STEPS_PER_SECOND
                                              : maxVelocitySteps;
  eipScanner::cip::CipUdint maxStepsPerSecondSquared =
      maxAccelerationSteps > MAX_ACCELERATION_STEPS_PER_SECOND_SQUARED
          ? MAX_ACCELERATION_STEPS_PER_SECOND_SQUARED
          : maxAccelerationSteps;

  motorOutputData.setVelocityLimit(maxStepsPerSecond);
  motorOutputData.setAccelerationLimit(maxStepsPerSecondSquared);
  motorOutputData.setDecelerationLimit(maxStepsPerSecondSquared);

  motorOutputData.setOutputRegisterFlag(MotorOutputData::Enable, true);
  motorOutputData.setOutputRegisterFlag(MotorOutputData::HomingMove, false);

  // reset unused flags
  motorOutputData.setOutputRegisterFlag(MotorOutputData::SoftwareEStop, false);
  motorOutputData.setOutputRegisterFlag(MotorOutputData::ClearAlerts, false);
  motorOutputData.setOutputRegisterFlag(MotorOutputData::ClearMotorFault,
                                        false);

  // actually write the values to the device
  setMotorOutput(clearlinkOutputObjectPtr, motorConnectorId, motorOutputData);
  clearlinkOutputObjectPtr->setAssembly();

  if (moveAlreadySet) {
    motorOutputData.setOutputRegisterFlag(loadMoveFlag, true);
    setMotorOutput(clearlinkOutputObjectPtr, motorConnectorId, motorOutputData);
    clearlinkOutputObjectPtr->setAssembly();
  }
}

void setMotorPositionMoveCommand(
    std::shared_ptr<clearlink::OutputAssemblyObject> clearlinkOutputObjectPtr,
    uint8_t motorConnectorId, int positionSetPoint,
    eipScanner::cip::CipUdint maxVelocitySteps,
    eipScanner::cip::CipUdint maxAccelerationSteps, bool absoluteMove) {

  clearlinkOutputObjectPtr->getAssembly();

  eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
      << "Motor is ready to POSITIONAL move";

  MotorOutputData motorOutputData =
      getMotorOutput(clearlinkOutputObjectPtr, motorConnectorId);

  motorOutputData.setMoveDistance(positionSetPoint);
  motorOutputData.setOutputRegisterFlag(
      MotorOutputData::OutputFlag::AbsoluteMove, absoluteMove);
  motorOutputData.setOutputRegisterFlag(
      MotorOutputData::OutputFlag::LoadVelocityMove, false);

  loadMotorMoveCommand(clearlinkOutputObjectPtr, motorConnectorId,
                       MotorOutputData::OutputFlag::LoadPositionMove,
                       maxVelocitySteps, maxAccelerationSteps);

  eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
      << "Motor is moving POSITIONALLY";
}

void unsetMotorPositionMoveCommand(
    std::shared_ptr<clearlink::InputAssemblyObject> /*clearlinkInputObjectPtr*/,
    std::shared_ptr<clearlink::OutputAssemblyObject> clearlinkOutputObjectPtr,
    uint8_t motorConnectorId) {
  eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
      << "Motor finished moving to POSITION, un-latching LoadPositionMove";

  MotorOutputData motorOutputData =
      getMotorOutput(clearlinkOutputObjectPtr, motorConnectorId);

  motorOutputData.setOutputRegisterFlag(MotorOutputData::LoadPositionMove,
                                        false);
  motorOutputData.setOutputRegisterFlag(MotorOutputData::Enable, false);

  setMotorOutput(clearlinkOutputObjectPtr, motorConnectorId, motorOutputData);
  clearlinkOutputObjectPtr->setAssembly();
}

MoveInstructionState moveToMotorPositionNonBlocking(
    std::shared_ptr<clearlink::InputAssemblyObject> clearlinkInputObjectPtr,
    std::shared_ptr<clearlink::OutputAssemblyObject> clearlinkOutputObjectPtr,
    uint8_t motorConnectorId, int positionSetPoint,
    eipScanner::cip::CipUdint maxVelocitySteps,
    eipScanner::cip::CipUdint maxAccelerationSteps, bool absoluteMove) {

  auto motorOutputData =
      getMotorOutput(clearlinkOutputObjectPtr, motorConnectorId);

  auto motorInputData =
      getMotorInput(clearlinkInputObjectPtr, motorConnectorId);

  int32_t previouslySetTargetPosition = motorOutputData.getMoveDistance();
  int32_t currentMotorPosition = motorInputData.getCommandedPosition();

  bool positionMoveCommanded =
      motorInputData.hasMotorStatus(MotorInputData::PositionalMove);
  bool absolutePositionCommanded =
      motorOutputData.hasFlagSet(MotorOutputData::AbsoluteMove);
  bool positionAlreadySet = positionSetPoint == previouslySetTargetPosition &&
                            positionMoveCommanded &&
                            absoluteMove == absolutePositionCommanded;

  bool motorInMotion =
      motorInputData.hasMotorStatus(MotorInputData::StepsActive);

  // set the new position if:
  // 1. The motor is not currently at the desired position
  // 2. The motor is not currently moving to the desired velocity

  if (positionAlreadySet &&
      motorInputData.hasMotorStatus(MotorInputData::AtTargetPosition)) {
    unsetMotorPositionMoveCommand(clearlinkInputObjectPtr,
                                  clearlinkOutputObjectPtr, motorConnectorId);
    return MoveInstructionState::COMPLETED;
  }

  if (positionAlreadySet && positionSetPoint == currentMotorPosition &&
      !motorInMotion) {
    // Move has already been completed
    return MoveInstructionState::COMPLETED;
  }

  if (positionAlreadySet &&
      motorInputData.hasMotorStatus(MotorInputData::LoadPositionMoveAck)) {
    // The move is currently happening
    return MoveInstructionState::IN_PROGRESS;
  }

  if (!faultsClearedSuccessfully(clearlinkInputObjectPtr,
                                 clearlinkOutputObjectPtr, motorConnectorId)) {
    return MoveInstructionState::FAULTED;
  }

  setMotorPositionMoveCommand(clearlinkOutputObjectPtr, motorConnectorId,
                              positionSetPoint, maxVelocitySteps,
                              maxAccelerationSteps, absoluteMove);
  return MoveInstructionState::IN_PROGRESS;
}

int main() {
  // Get the clearlinkIO (given a variable IP address and the default
  // Ethernet/IP port)
  ClearlinkIO clearlinkRepresentation =
      createClearlinkIOObject("192.168.1.71", 0xAF12);

  uint8_t motorConnector = 0;

  initializeMotorConfiguration(clearlinkRepresentation.configPtr,
                               motorConnector, -1, -1, -1, -1, 0, 0);

  // clear any existing faults
  while (!faultsClearedSuccessfully(clearlinkRepresentation.inputPtr,
                                    clearlinkRepresentation.outputPtr,
                                    motorConnector)) {
    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }

  // perform a move
  MoveInstructionState movementState = MoveInstructionState::COMPLETED;
  eipScanner::cip::CipUdint maxVelocitySteps = 5000;
  eipScanner::cip::CipUdint maxAccelerationSteps = 10000;
  do {
    movementState = moveToMotorPositionNonBlocking(
        clearlinkRepresentation.inputPtr, clearlinkRepresentation.outputPtr,
        motorConnector, 1000, maxVelocitySteps, maxAccelerationSteps, false);
  } while (movementState != MoveInstructionState::COMPLETED);
}
