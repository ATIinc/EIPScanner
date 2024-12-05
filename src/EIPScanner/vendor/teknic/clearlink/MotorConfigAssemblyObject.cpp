//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/MotorConfigAssemblyObject.h"
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

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
