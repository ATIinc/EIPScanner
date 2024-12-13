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
    : BaseAssemblyData(), _aI0Range(DEFAULT_AI0_RANGE_VALUE),
      _aI1Range(DEFAULT_AI1_RANGE_VALUE), _aI2Range(DEFAULT_AI2_RANGE_VALUE),
      _aI3Range(DEFAULT_AI3_RANGE_VALUE), _aO0Range(DEFAULT_AO0_RANGE_VALUE),
      _dopPWMFrequency(), _ccioEnable(), _reservedPadding(PADDING_BYTES_SIZE) {}

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
