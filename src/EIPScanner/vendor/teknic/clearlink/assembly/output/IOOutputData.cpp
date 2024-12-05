//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/IOOutputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {

IOOutputData::IOOutputData()
    : BaseAssemblyData(), _aopValue(), _dopValue(DOP_VALUE_SIZE),
      _dopPWM(DOP_PWM_SIZE), _reservedPadding(PADDING_BYTES_SIZE),
      _ccioOutputData(), _encoderAddToPosition() {}

std::vector<BaseAssemblyData::DataFieldReference>
IOOutputData::_getDataFieldReferences() {

  return {
      std::ref(_aopValue),       std::ref(_dopValue),
      std::ref(_dopPWM),         std::ref(_reservedPadding),
      std::ref(_ccioOutputData), std::ref(_encoderAddToPosition)
  };
}
} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
