//
// Created by Jan Ritzenhoff on 8/28/2024
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
  return {{std::ref(_ioInputData)},     {std::ref(_encoderInputData)},
          {std::ref(_motor0InputData)}, {std::ref(_motor1InputData)},
          {std::ref(_motor2InputData)}, {std::ref(_motor3InputData)},
          {std::ref(_serialAsciiData)}};
}

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
