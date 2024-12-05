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
    : BaseAssemblyData(), _encoderVelocityResolution(),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
EncoderConfigData::_getDataFieldReferences() {

  return {std::ref(_encoderVelocityResolution), std::ref(_reservedPadding)};
}
} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
