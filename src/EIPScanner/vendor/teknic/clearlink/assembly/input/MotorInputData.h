//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - Motor Input Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_MOTORINPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_MOTORINPUTDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {

/**
 * @class MotorInputData
 *
 * @brief Implements the Step & Direction Motor Input Data section
 */
class MotorInputData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  MotorInputData();

private:
  virtual std::vector<DataFieldReference> _getDataFieldReferences();

  // CONSTANTS
  static const size_t ENCODER_STATUS_SIZE = 1; // 2 bits
  static const size_t PADDING_BYTES_SIZE = 2;

  // Actual field members
  eipScanner::cip::CipDint _encoderPosition;
  eipScanner::cip::CipDint _encoderVelocity;
  eipScanner::cip::CipDint _encoderIndexPosition;
  std::vector<eipScanner::cip::CipBool> _encoderStatus;
  std::vector<eipScanner::cip::CipByte> _reservedPadding;
};

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_MOTORINPUTDATA_H
