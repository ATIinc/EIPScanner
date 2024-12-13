//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/EncoderConfigData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {

EncoderConfigData::EncoderConfigData()
    : BaseAssemblyData(),
      _encoderVelocityResolution(DEFAULT_ENCODER_VELOCITY_RESOLUTION_VALUE),
      _reservedSetByte(DEFAULT_RESERVED_SET_BYTE_VALUE),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
EncoderConfigData::_getDataFieldReferences() {

  return {std::ref(_encoderVelocityResolution), std::ref(_reservedSetByte),
          std::ref(_reservedPadding)};
}
} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
