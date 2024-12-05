#include <memory>

#include "EIPScanner/vendor/teknic/clearlink/assembly/config/MotorConfigData.h"
#include <EIPScanner/cip/Types.h>
#include <EIPScanner/vendor/teknic/clearlink/ConfigAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/InputAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/OutputAssemblyObject.h>
#include <stdexcept>

using namespace eipScanner::vendor::teknic;
using eipScanner::vendor::teknic::clearlink::assembly::config::MotorConfigData;

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
    throw std::runtime_error("Unknown motor connector ID " +
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
    throw std::runtime_error("Unknown motor connector ID " +
                             std::to_string(motorConnectorId));
  }
}

// ------------------------------
// initialize the object assembly wrappers
// -------------
ClearlinkIO createClearlinkIOObjects(std::string clearlinkIpAddress,
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

/*
void initializeMovementLimits(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectPtr);

bool faultsClearedSuccessfully(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

bool faultsClearedSuccessfully(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

void loadMotorMoveCommand(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectPtr, SDMotorOutputObject::OutputFlag loadMoveFlag, CipUdint
maxVelocitySteps, CipUdint maxAccelerationSteps);

void setMotorPositionMoveCommand(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectPtr, int positionSetPoint, CipUdint maxVelocitySteps, CipUdint
maxAccelerationSteps, bool absoluteMove);

void unsetMotorPositionMoveCommand(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

MoveInstructionState
moveToMotorPositionNonBlocking(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr,
                                                    int positionSetPoint,
                                                    CipUdint maxVelocitySteps,
                                                    CipUdint
maxAccelerationSteps, bool absoluteMove = false);

void setMotorVelocityMoveCommand(std::shared_ptr<SDMotorOutputObject>
motorOutputObjectptr, int velocitySetPoint, CipUdint maxAccelerationSteps);

void unsetMotorVelocityMoveCommand(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

MoveInstructionState
moveToMotorVelocityNonBlocking(std::shared_ptr<SDMotorInputObject>
motorInputObjectPtr, std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr,
                                                    int velocitySetPoint,
                                                    CipUdint
maxAccelerationSteps);

bool homeMotor(std::shared_ptr<SDMotorInputObject> motorInputObjectPtr,
               std::shared_ptr<SDMotorOutputObject> motorOutputObjectPtr);

} // namespace motorIO

} // namespace motorController

*/

int main() {
  // Get the clearlinkIO (given a variable IP address and the default
  // Ethernet/IP port)
  ClearlinkIO clearlinkRepresentation =
      createClearlinkIOObjects("192.168.1.54", 0xAF12);

  initializeMotorConfiguration(clearlinkRepresentation.configPtr, 0, -1, -1, -1,
                               -1, 0, 0);

  // write a positional move
}
