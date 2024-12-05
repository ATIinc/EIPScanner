//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - Motor Input Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_CLEARLINKINPUTASSEMBLY_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_CLEARLINKINPUTASSEMBLY_H

#include <functional>

#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/EncoderInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/IOInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/MotorInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/SerialAsciiInputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

/**
 * @class MotorInputAssembly
 *
 * @brief Implements the Step & Direction Motor Input Data section
 */
class InputAssemblyObject : public BaseAssemblyObject {
public:
  static const eipScanner::cip::CipUint INSTANCE_ID = 0x64;

  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  InputAssemblyObject(const eipScanner::SessionInfoIf::SPtr sessionInfo,
                      const eipScanner::MessageRouter::SPtr messageRouter);

  assembly::input::MotorInputData getMotor0InputData();
  assembly::input::MotorInputData getMotor1InputData();
  assembly::input::MotorInputData getMotor2InputData();
  assembly::input::MotorInputData getMotor3InputData();

  // -------------------------------------------------------------

  void setMotor0InputData(assembly::input::MotorInputData motor0InputData);
  void setMotor1InputData(assembly::input::MotorInputData motor1InputData);
  void setMotor2InputData(assembly::input::MotorInputData motor2InputData);
  void setMotor3InputData(assembly::input::MotorInputData motor3InputData);

private:
  std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
  _getAssemblyDataFieldReferences() override;

  // Actual field members
  assembly::input::IOInputData _ioInputData;
  assembly::input::EncoderInputData _encoderInputData;
  assembly::input::MotorInputData _motor0InputData;
  assembly::input::MotorInputData _motor1InputData;
  assembly::input::MotorInputData _motor2InputData;
  assembly::input::MotorInputData _motor3InputData;
  assembly::input::SerialAsciiInputData _serialAsciiInputData;
};

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_CLEARLINKINPUTASSEMBLY_H
