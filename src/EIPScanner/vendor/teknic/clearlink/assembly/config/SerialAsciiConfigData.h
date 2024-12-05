//
// Created by Jan Ritzenhoff on 12/5/2024
//

// Based on:
//	Assembly Object - IO Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=21

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_SERIALASCIICONFIGDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_SERIALASCIICONFIGDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {
/**
 * @class SerialAsciiConfigData
 *
 * @brief Implements the Step & Direction Serial Ascii Config Data section
 */
class SerialAsciiConfigData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  SerialAsciiConfigData();

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // Actual field members
  eipScanner::cip::CipUdint _serialBaudRate;
  eipScanner::cip::CipDword _inputStartDelimiter;
  eipScanner::cip::CipDword _inputEndDelimiter;
  eipScanner::cip::CipDword _outputStartDelimiter;
  eipScanner::cip::CipDword _outputEndDelimiter;
  eipScanner::cip::CipUdint _inputTimeout;
};

} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_SERIALASCIICONFIGDATA_H
