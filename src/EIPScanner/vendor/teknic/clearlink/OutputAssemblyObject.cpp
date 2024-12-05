//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/OutputAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

OutputAssemblyObject::OutputAssemblyObject(
    const eipScanner::SessionInfoIf::SPtr sessionInfo,
    const eipScanner::MessageRouter::SPtr messageRouter)
    : BaseAssemblyObject(INSTANCE_ID, sessionInfo, messageRouter) {}

std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
OutputAssemblyObject::_getAssemblyDataFieldReferences() {

  return {{std::ref(_ioOutputData)},     {std::ref(_motor0OutputData)},
          {std::ref(_motor1OutputData)}, {std::ref(_motor2OutputData)},
          {std::ref(_motor3OutputData)}, {std::ref(_serialAsciiOutputData)}};
}

assembly::output::MotorOutputData OutputAssemblyObject::getMotor0OutputData() {
  return _motor0OutputData;
}

void OutputAssemblyObject::setMotor0OutputData(
    assembly::output::MotorOutputData motor0OutputData) {
  _motor0OutputData = motor0OutputData;
}

// -------------------------------------------------------------

assembly::output::MotorOutputData OutputAssemblyObject::getMotor1OutputData() {
  return _motor1OutputData;
}

void OutputAssemblyObject::setMotor1OutputData(
    assembly::output::MotorOutputData motor1OutputData) {
  _motor1OutputData = motor1OutputData;
}

// -------------------------------------------------------------

assembly::output::MotorOutputData OutputAssemblyObject::getMotor2OutputData() {
  return _motor2OutputData;
}

void OutputAssemblyObject::setMotor2OutputData(
    assembly::output::MotorOutputData motor2OutputData) {
  _motor2OutputData = motor2OutputData;
}

// -------------------------------------------------------------

assembly::output::MotorOutputData OutputAssemblyObject::getMotor3OutputData() {
  return _motor3OutputData;
}

void OutputAssemblyObject::setMotor3OutputData(
    assembly::output::MotorOutputData motor3OutputData) {
  _motor3OutputData = motor3OutputData;
}

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
