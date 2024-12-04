//
// Created by Jan Ritzenhoff on 8/28/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/EncoderInputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {

EncoderInputData::EncoderInputData()
    : BaseAssemblyData(), _encoderPosition(), _encoderVelocity(),
      _encoderIndexPosition(), _encoderStatus(ENCODER_STATUS_SIZE),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
EncoderInputData::_getDataFieldReferences() {
  return {

      std::ref(_encoderPosition), std::ref(_encoderVelocity),
      std::ref(_encoderIndexPosition), std::ref(_encoderStatus),
      std::ref(_reservedPadding)};
}
} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
