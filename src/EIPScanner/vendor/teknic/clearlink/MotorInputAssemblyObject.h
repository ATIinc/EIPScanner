//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - Motor Input Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_MOTORINPUTASSEMBLY_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_MOTORINPUTASSEMBLY_H

#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/EncoderInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/IOInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/MotorInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/SerialAsciiInputData.h"
#include <functional>

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

/**
 * @class MotorInputAssembly
 *
 * @brief Implements the Step & Direction Motor Input Data section
 */
class MotorInputAssemblyObject : public BaseAssemblyObject {
public:
  static const eipScanner::cip::CipUint INSTANCE_ID = 0x64;

  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  MotorInputAssemblyObject(const eipScanner::SessionInfoIf::SPtr sessionInfo,
                           const eipScanner::MessageRouter::SPtr messageRouter);

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
  assembly::input::SerialAsciiInputData _serialAsciiData;
};

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_MOTORINPUTASSEMBLY_H
