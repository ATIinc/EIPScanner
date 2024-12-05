//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/MotorOutputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {

MotorOutputData::MotorOutputData()
    : BaseAssemblyData(), _moveDistance(), _velocityLimit(),
      _accelerationLimit(), _decelerationLimit(), _jogVelocity(),
      _addToPosition(), _outputRegister() {}

std::vector<BaseAssemblyData::DataFieldReference>
MotorOutputData::_getDataFieldReferences() {
  return {std::ref(_moveDistance),      std::ref(_velocityLimit),
          std::ref(_accelerationLimit), std::ref(_decelerationLimit),
          std::ref(_jogVelocity),       std::ref(_addToPosition),
          std::ref(_outputRegister)};
}
} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
