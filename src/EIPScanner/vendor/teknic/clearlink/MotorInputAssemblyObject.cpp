//
// Created by Jan Ritzenhoff on 12/4/2024
//
#include "EIPScanner/vendor/teknic/clearlink/MotorInputAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

MotorInputAssemblyObject::MotorInputAssemblyObject(
    const eipScanner::SessionInfoIf::SPtr sessionInfo,
    const eipScanner::MessageRouter::SPtr messageRouter)
    : BaseAssemblyObject(INSTANCE_ID, sessionInfo, messageRouter) {}

std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
MotorInputAssemblyObject::_getAssemblyDataFieldReferences() {
  return {{std::ref(_ioInputData)},         {std::ref(_encoderInputData)},
          {std::ref(_motor0InputData)},     {std::ref(_motor1InputData)},
          {std::ref(_motor2InputData)},     {std::ref(_motor3InputData)},
          {std::ref(_serialAsciiInputData)}};
}

assembly::input::MotorInputData MotorInputAssemblyObject::getMotor0InputData() {
  return _motor0InputData;
}

void MotorInputAssemblyObject::setMotor0InputData(
    assembly::input::MotorInputData motor0InputData) {
  _motor0InputData = motor0InputData;
}

// -------------------------------------------------------------

assembly::input::MotorInputData MotorInputAssemblyObject::getMotor1InputData() {
  return _motor1InputData;
}

void MotorInputAssemblyObject::setMotor1InputData(
    assembly::input::MotorInputData motor1InputData) {
  _motor1InputData = motor1InputData;
}

// -------------------------------------------------------------

assembly::input::MotorInputData MotorInputAssemblyObject::getMotor2InputData() {
  return _motor2InputData;
}

void MotorInputAssemblyObject::setMotor2InputData(
    assembly::input::MotorInputData motor2InputData) {
  _motor2InputData = motor2InputData;
}

// -------------------------------------------------------------

assembly::input::MotorInputData MotorInputAssemblyObject::getMotor3InputData() {
  return _motor3InputData;
}

void MotorInputAssemblyObject::setMotor3InputData(
    assembly::input::MotorInputData motor3InputData) {
  _motor3InputData = motor3InputData;
}

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
