//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - Serial Ascii Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=19

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_SERIALASCIIOUTPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_SERIALASCIIOUTPUTDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {

/**
 * @class SerialAsciiOutputData
 *
 * @brief Implements the Step & Direction Serial Ascii Output Data section
 */
class SerialAsciiOutputData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  SerialAsciiOutputData();

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // CONSTANTS
  static const size_t OUTPUT_DATA_SIZE = 128;

  // Actual field members
  eipScanner::cip::CipDword _serialConfig;
  eipScanner::cip::CipUdint _inputSequenceAck;
  eipScanner::cip::CipUdint _outputSize;
  eipScanner::cip::CipUdint _outputSequence;
  std::vector<eipScanner::cip::CipUsint> _outputData;
};

} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_SERIALASCIIOUTPUTDATA_H
