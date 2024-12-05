//
// Created by Jan Ritzenhoff on 12/5/2024
//

// Based on:
//	Assembly Object - IO Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=20

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_MOTORCONFIGDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_MOTORCONFIGDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {
/**
 * @class MotorConfigData
 *
 * @brief Implements the Step & Direction Motor Config Data section
 */
class MotorConfigData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  MotorConfigData();

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // CONSTANTS
  static const size_t PADDING_BYTES_SIZE = 1;

  // Actual field members
  eipScanner::cip::CipDword _configRegister;
  eipScanner::cip::CipDint _followDivisor;
  eipScanner::cip::CipDint _followMultiplier;
  eipScanner::cip::CipDint _maxDeceleration;
  eipScanner::cip::CipDint _softLimitPosition1;
  eipScanner::cip::CipDint _softLimitPosition2;
  eipScanner::cip::CipSint _positiveLimitConnector;
  eipScanner::cip::CipSint _negativeLimitConnector;
  eipScanner::cip::CipSint _homeSensorConnector;
  eipScanner::cip::CipSint _brakeOutputConnector;
  eipScanner::cip::CipSint _stopSensorConnector;
  eipScanner::cip::CipSint _triggerPositionCaptureConnector;
  eipScanner::cip::CipSint _followAxis;
  std::vector<eipScanner::cip::CipByte> _reservedPadding;
};

} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_CONFIG_MOTORCONFIGDATA_H
