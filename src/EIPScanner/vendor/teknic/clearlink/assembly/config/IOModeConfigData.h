//
// Created by Jan Ritzenhoff on 12/5/2024
//

// Based on:
//	Assembly Object - IO Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=20

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_IOMODECONFIGDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_IOMODECONFIGDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {
/**
 * @class IOModeConfigData
 *
 * @brief Implements the Step & Direction IO Mode Config Data section
 */
class IOModeConfigData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  IOModeConfigData();

  enum class AnalogInputRange : cip::CipUsint {
    ZERO_TO_TEN_VOLTS = 2,
    AS_DIGITAL_INPUT = 100,
  };

  enum class AnalogOutputRange : cip::CipUsint {
    FOUR_TO_TWENTY_MILLIAMPS = 0,
    ZERO_TO_TWENTY_MILLIAMPS = 2,
    AS_DIGITAL_OUTPUT = 100,
  };

  enum class PWMFrequency : cip::CipBool {
    FIVE_HUNDRED_HZ = 0,
    EIGHT_KILO_HZ = 1,
  };

  eipScanner::cip::CipUsint getAI0Range();
  eipScanner::cip::CipUsint getAI1Range();
  eipScanner::cip::CipUsint getAI2Range();
  eipScanner::cip::CipUsint getAI3Range();
  eipScanner::cip::CipUsint getAO0Range();
  eipScanner::cip::CipBool getDopPWMFrequency();

  // -------------------------------------------------------------

  void setAI0Range(AnalogInputRange analogInput0Range);
  void setAI1Range(AnalogInputRange analogInput1Range);
  void setAI2Range(AnalogInputRange analogInput2Range);
  void setAI3Range(AnalogInputRange analogInput3Range);
  void setAO0Range(AnalogOutputRange analogOutput0Range);
  void setDopPWMFrequency(PWMFrequency dopPWMFrequency);

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // CONSTANTS
  static const size_t PADDING_BYTES_SIZE = 1;

  // CONSTANT DEFAULTS
  eipScanner::cip::CipUsint DEFAULT_AI0_RANGE_VALUE =
      static_cast<cip::CipUsint>(AnalogInputRange::AS_DIGITAL_INPUT);
  eipScanner::cip::CipUsint DEFAULT_AI1_RANGE_VALUE =
      static_cast<cip::CipUsint>(AnalogInputRange::AS_DIGITAL_INPUT);
  eipScanner::cip::CipUsint DEFAULT_AI2_RANGE_VALUE =
      static_cast<cip::CipUsint>(AnalogInputRange::AS_DIGITAL_INPUT);
  eipScanner::cip::CipUsint DEFAULT_AI3_RANGE_VALUE =
      static_cast<cip::CipUsint>(AnalogInputRange::AS_DIGITAL_INPUT);
  eipScanner::cip::CipUsint DEFAULT_AO0_RANGE_VALUE =
      static_cast<cip::CipUsint>(AnalogOutputRange::AS_DIGITAL_OUTPUT);
  eipScanner::cip::CipBool DEFAULT_PWM_FREQUENCY =
      static_cast<cip::CipBool>(PWMFrequency::FIVE_HUNDRED_HZ);
  eipScanner::cip::CipBool DEFAULT_CCIO_ENABLE = false;

  // Actual field members
  eipScanner::cip::CipUsint _aI0Range;
  eipScanner::cip::CipUsint _aI1Range;
  eipScanner::cip::CipUsint _aI2Range;
  eipScanner::cip::CipUsint _aI3Range;
  eipScanner::cip::CipUsint _aO0Range;
  eipScanner::cip::CipBool _dopPWMFrequency;
  eipScanner::cip::CipBool _ccioEnable;
  std::vector<eipScanner::cip::CipByte> _reservedPadding;
};

} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_IOMODECONFIGDATA_H
