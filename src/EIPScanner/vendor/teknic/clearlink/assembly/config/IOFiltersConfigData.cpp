//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/IOFiltersConfigData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {

IOFiltersConfigData::IOFiltersConfigData()
    : BaseAssemblyData(),
      _aipFilters(AIP_FILTERS_SIZE, DEFAULT_AIP_FILTERS_VALUE),
      _dipFilters(DIP_FILTERS_SIZE, DEFAULT_DIP_FILTERS_VALUE),
      _ccioFilters(CCIO_FILTERS_SIZE, DEFAULT_CCIO_FILTERS_VALUE) {}

std::vector<BaseAssemblyData::DataFieldReference>
IOFiltersConfigData::_getDataFieldReferences() {
  return {std::ref(_aipFilters), std::ref(_dipFilters), std::ref(_ccioFilters)};
}
} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
