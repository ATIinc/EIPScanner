//
// Created by Jan Ritzenhoff on 8/28/2024
//
#include "EIPScanner/vendor/teknic/clearlink/MotorInputAssembly.h"
#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

MotorInputAssembly::MotorInputAssembly(
    const eipScanner::SessionInfoIf::SPtr sessionInfo,
    const eipScanner::MessageRouter::SPtr messageRouter)
    : BaseAssemblyObject(INSTANCE_ID, sessionInfo, messageRouter) {}

std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
MotorInputAssembly::_getAssemblyDataFieldReferences() {
  return {
    std::ref(_ioInputData), std::ref(_encoderInputData),
        std::ref(_motor0InputData), std::ref(_motor1InputData),
        std::ref(_motor2InputData), std::ref(_motor3InputData),
        std::ref(_serialAsciiData)
  }
}

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
