//
// Created by Jan Ritzenhoff on 12/5/2024
//

// Based on:
//	Assembly Object - IO Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=19

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_IOOUTPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_IOOUTPUTDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"
#include <cstdint>

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {
/**
 * @class IOOutputData
 *
 * @brief Implements the Step & Direction IO Output Data section
 */
class IOOutputData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  IOOutputData();

  // -------------------------------------------------------------

  enum class DigitalOutput : uint8_t {
    IO_0 = 0,
    IO_1 = 1,
    IO_2 = 2,
    IO_3 = 3,
    IO_4 = 4,
    IO_5 = 5,
  };

  // Used to configure IO_0 as a digital output rather than an analog output
  eipScanner::cip::CipUsint DEFAULT_PWM_VALUE = 100;

  // -------------------------------------------------------------

  eipScanner::cip::CipInt getAnalogOutputValue();
  bool getDigitalOutputValue(DigitalOutput output);
  eipScanner::cip::CipUsint getDigitalOutputPWM(DigitalOutput output);

  // -------------------------------------------------------------

  void setAnalogOutputValue(eipScanner::cip::CipInt analogValue);
  void setDigitalOutputValue(DigitalOutput output, bool outputValue);
  void setDigitalOutputPWM(DigitalOutput output,
                           eipScanner::cip::CipUsint pwmValue);

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // CONSTANTS
  static const size_t DOP_VALUE_SIZE = 2; // 6 bits
  static const size_t DOP_PWM_SIZE = 6;
  static const size_t PADDING_BYTES_SIZE = 2;

  // Actual field members
  eipScanner::cip::CipInt _aopValue;
  std::vector<eipScanner::cip::CipBool> _dopValue;
  std::vector<eipScanner::cip::CipUsint> _dopPWM;
  std::vector<eipScanner::cip::CipByte> _reservedPadding;
  eipScanner::cip::CipUlint _ccioOutputData;
  eipScanner::cip::CipDint _encoderAddToPosition;
};

} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_IOOUTPUTDATA_H
