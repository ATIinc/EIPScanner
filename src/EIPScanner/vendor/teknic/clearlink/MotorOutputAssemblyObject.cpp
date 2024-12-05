//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/MotorOutputAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

MotorOutputAssemblyObject::MotorOutputAssemblyObject(
    const eipScanner::SessionInfoIf::SPtr sessionInfo,
    const eipScanner::MessageRouter::SPtr messageRouter)
    : BaseAssemblyObject(INSTANCE_ID, sessionInfo, messageRouter) {}

std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
MotorOutputAssemblyObject::_getAssemblyDataFieldReferences() {

  return {{std::ref(_ioOutputData)},     {std::ref(_motor0OutputData)},
          {std::ref(_motor1OutputData)}, {std::ref(_motor2OutputData)},
          {std::ref(_motor3OutputData)}, {std::ref(_serialAsciiOutputData)}};
}

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
