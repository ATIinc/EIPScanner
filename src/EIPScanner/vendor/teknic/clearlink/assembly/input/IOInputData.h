//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - IO Input Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_IOINPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_IOINPUTDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {
/**
 * @class IOInputData
 *
 * @brief Implements the Step & Direction IO Input Data section
 */
class IOInputData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  IOInputData();

  // -------------------------------------------------------------

  void setDipValue(const std::vector<eipScanner::cip::CipBool> dipValue);
  void setDipStatus(const std::vector<eipScanner::cip::CipBool> dipStatus);
  void setAipValue(const std::vector<eipScanner::cip::CipUint> aipValue);

  // -------------------------------------------------------------

  const std::vector<eipScanner::cip::CipBool> getDipValue();
  const std::vector<eipScanner::cip::CipBool> getDipStatus();
  const std::vector<eipScanner::cip::CipUint> getAipValue();

private:
  virtual std::vector<DataFieldReference> _getDataFieldReferences();

  // CONSTANTS
  static const size_t DIP_VALUE_SIZE = 2;  // 13 bits
  static const size_t DIP_STATUS_SIZE = 2; // 13 bits
  static const size_t AIP_VALUE_SIZE = 4;
  static const size_t AIOP_STATUS_SIZE = 2; // 5 bits
  static const size_t DOP_STATUS_SIZE = 2;  // 6 bits
  static const size_t PADDING_BYTES_SIZE = 2;

  // Actual field members
  std::vector<eipScanner::cip::CipBool> _dipValue;
  std::vector<eipScanner::cip::CipBool> _dipStatus;
  // NOTE: Cheating a little bit because no signed-int16 buffering exists
  std::vector<eipScanner::cip::CipUint> _aipValue;
  std::vector<eipScanner::cip::CipBool> _aiopStatus;
  std::vector<eipScanner::cip::CipBool> _dopStatus;
  eipScanner::cip::CipUlint _ccioInputValue;
  eipScanner::cip::CipUlint _ccioStatus;
  eipScanner::cip::CipSint _ccioBoardCount;
  std::vector<eipScanner::cip::CipByte> _reservedPadding;
};

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_IOINPUTDATA_H
