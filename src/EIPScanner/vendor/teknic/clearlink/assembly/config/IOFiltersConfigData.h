//
// Created by Jan Ritzenhoff on 12/5/2024
//

// Based on:
//	Assembly Object - IO Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=20

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_IOFILTERSCONFIGDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_IOFILTERSCONFIGDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {
/**
 * @class IOFiltersConfigData
 *
 * @brief Implements the Step & Direction IO Filters Data section
 */
class IOFiltersConfigData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  IOFiltersConfigData();

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // CONSTANTS
  static const size_t AIP_FILTERS_SIZE = 4;
  static const size_t DIP_FILTERS_SIZE = 26;
  static const size_t CCIO_FILTERS_SIZE = 8;

  // CONSTANT DEFAULTS
  const eipScanner::cip::CipUsint DEFAULT_AIP_FILTERS_VALUE = 10;
  const eipScanner::cip::CipUint DEFAULT_DIP_FILTERS_VALUE = 10000;
  const eipScanner::cip::CipUsint DEFAULT_CCIO_FILTERS_VALUE = 10;

  // Actual field members
  std::vector<eipScanner::cip::CipUsint> _aipFilters;
  std::vector<eipScanner::cip::CipUint> _dipFilters;
  std::vector<eipScanner::cip::CipUsint> _ccioFilters;
};

} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_IOFILTERSCONFIGDATA_H
