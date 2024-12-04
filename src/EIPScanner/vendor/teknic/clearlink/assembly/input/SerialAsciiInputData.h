//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - Motor Input Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_SERIALASCIIINPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_SERIALASCIIINPUTDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {

/**
 * @class SerialAsciiInputData
 *
 * @brief Implements the Step & Direction Motor Input Data section
 */
class SerialAsciiInputData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  SerialAsciiInputData();

private:
  virtual std::vector<DataFieldReference> _getDataFieldReferences();

  // CONSTANTS
  static const size_t INPUT_DATA_SIZE = 128;

  // Actual field members
  eipScanner::cip::CipDword _serialStatus;
  eipScanner::cip::CipUdint _outputCharCount;
  eipScanner::cip::CipUdint _inputCharCount;
  eipScanner::cip::CipUdint _outputSequenceAck;
  eipScanner::cip::CipUdint _inputSize;
  eipScanner::cip::CipUdint _inputSequence;
  std::vector<eipScanner::cip::CipUsint> _inputData;
};

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_SERIALASCIIINPUTDATA_H
