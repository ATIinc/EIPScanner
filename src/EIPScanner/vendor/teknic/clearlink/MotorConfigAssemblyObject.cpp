//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/MotorConfigAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

MotorConfigAssemblyObject::MotorConfigAssemblyObject(
    const eipScanner::SessionInfoIf::SPtr sessionInfo,
    const eipScanner::MessageRouter::SPtr messageRouter)
    : BaseAssemblyObject(INSTANCE_ID, sessionInfo, messageRouter) {}

std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
MotorConfigAssemblyObject::_getAssemblyDataFieldReferences() {

  return {{std::ref(_ioModeConfigData)},  {std::ref(_ioFiltersConfigData)},
          {std::ref(_encoderConfigData)}, {std::ref(_motor0ConfigData)},
          {std::ref(_motor1ConfigData)},  {std::ref(_motor2ConfigData)},
          {std::ref(_motor3ConfigData)},  {std::ref(_serialAsciiConfigData)}};
}

assembly::config::MotorConfigData
MotorConfigAssemblyObject::getMotor0ConfigData() {
  return _motor0ConfigData;
}

void MotorConfigAssemblyObject::setMotor0ConfigData(
    assembly::config::MotorConfigData motor0ConfigData) {
  _motor0ConfigData = motor0ConfigData;
}
// -------------------------------------------------------------

assembly::config::MotorConfigData
MotorConfigAssemblyObject::getMotor1ConfigData() {
  return _motor1ConfigData;
}

void MotorConfigAssemblyObject::setMotor1ConfigData(
    assembly::config::MotorConfigData motor1ConfigData) {
  _motor1ConfigData = motor1ConfigData;
}
// -------------------------------------------------------------

assembly::config::MotorConfigData
MotorConfigAssemblyObject::getMotor2ConfigData() {
  return _motor2ConfigData;
}

void MotorConfigAssemblyObject::setMotor2ConfigData(
    assembly::config::MotorConfigData motor2ConfigData) {
  _motor2ConfigData = motor2ConfigData;
}
// -------------------------------------------------------------

assembly::config::MotorConfigData
MotorConfigAssemblyObject::getMotor3ConfigData() {
  return _motor3ConfigData;
}

void MotorConfigAssemblyObject::setMotor3ConfigData(
    assembly::config::MotorConfigData motor3ConfigData) {
  _motor3ConfigData = motor3ConfigData;
}

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
