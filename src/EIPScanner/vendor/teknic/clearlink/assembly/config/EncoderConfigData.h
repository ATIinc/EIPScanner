//
// Created by Jan Ritzenhoff on 12/5/2024
//

// Based on:
//	Assembly Object - IO Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=20

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_ENCODERSCONFIGDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_ENCODERSCONFIGDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {
/**
 * @class EncoderConfigData
 *
 * @brief Implements the Step & Direction Encoder Config Data section
 */
class EncoderConfigData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  EncoderConfigData();

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // CONSTANTS
  static const size_t PADDING_BYTES_SIZE = 4;

  // Actual field members
  eipScanner::cip::CipUdint _encoderVelocityResolution;
  std::vector<eipScanner::cip::CipByte> _reservedPadding;
};

} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_ENCODERSCONFIGDATA_H
