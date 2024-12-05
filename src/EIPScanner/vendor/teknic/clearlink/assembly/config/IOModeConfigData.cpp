//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/IOModeConfigData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {

IOModeConfigData::IOModeConfigData()
    : BaseAssemblyData(), _aI0Range(), _aI1Range(), _aI2Range(), _aI3Range(),
      _aO0Range(), _dopPWMFrequency(), _ccioEnable(),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
IOModeConfigData::_getDataFieldReferences() {

  return {std::ref(_aI0Range),   std::ref(_aI1Range),
          std::ref(_aI2Range),   std::ref(_aI3Range),
          std::ref(_aO0Range),   std::ref(_dopPWMFrequency),
          std::ref(_ccioEnable), std::ref(_reservedPadding)};
}
} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
