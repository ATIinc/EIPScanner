//
// Created by Jan Ritzenhoff on 12/4/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/MotorInputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {

MotorInputData::MotorInputData()
    : BaseAssemblyData(), _commandedPosition(), _commandedVelocity(),
      _targetPosition(), _targetVelocity(), _capturedPosition(),
      _measuredTorque(), _motorStatus(), _motorShutdowns() {}

std::vector<BaseAssemblyData::DataFieldReference>
MotorInputData::_getDataFieldReferences() {
  return {std::ref(_commandedPosition), std::ref(_commandedVelocity),
          std::ref(_targetPosition),    std::ref(_targetVelocity),
          std::ref(_capturedPosition),  std::ref(_measuredTorque),
          std::ref(_motorStatus),       std::ref(_motorShutdowns)};
}

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
