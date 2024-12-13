//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - Motor Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=20

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_CLEARLINKCONFIGASSEMBLY_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_CLEARLINKCONFIGASSEMBLY_H

#include <functional>

#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/EncoderConfigData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/IOFiltersConfigData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/IOModeConfigData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/MotorConfigData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/SerialAsciiConfigData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

/**
 * @class MotorConfigAssembly
 *
 * @brief Implements the Step & Direction Motor Config Data section
 */
class ConfigAssemblyObject : public BaseAssemblyObject {
public:
  static const eipScanner::cip::CipUint INSTANCE_ID = 0x96;

  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  ConfigAssemblyObject(const eipScanner::SessionInfoIf::SPtr sessionInfo,
                       const eipScanner::MessageRouter::SPtr messageRouter);

  assembly::config::MotorConfigData getMotor0ConfigData();
  assembly::config::MotorConfigData getMotor1ConfigData();
  assembly::config::MotorConfigData getMotor2ConfigData();
  assembly::config::MotorConfigData getMotor3ConfigData();

  // -------------------------------------------------------------

  void setMotor0ConfigData(assembly::config::MotorConfigData motor0ConfigData);
  void setMotor1ConfigData(assembly::config::MotorConfigData motor1ConfigData);
  void setMotor2ConfigData(assembly::config::MotorConfigData motor2ConfigData);
  void setMotor3ConfigData(assembly::config::MotorConfigData motor3ConfigData);

private:
  std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
  _getAssemblyDataFieldReferences() override;

  // Actual field members
  assembly::config::IOModeConfigData _ioModeConfigData;
  assembly::config::IOFiltersConfigData _ioFiltersConfigData;
  assembly::config::EncoderConfigData _encoderConfigData;
  assembly::config::MotorConfigData _motor0ConfigData;
  assembly::config::MotorConfigData _motor1ConfigData;
  assembly::config::MotorConfigData _motor2ConfigData;
  assembly::config::MotorConfigData _motor3ConfigData;
  assembly::config::SerialAsciiConfigData _serialAsciiConfigData;
};

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_CLEARLINKCONFIGASSEMBLY_H
