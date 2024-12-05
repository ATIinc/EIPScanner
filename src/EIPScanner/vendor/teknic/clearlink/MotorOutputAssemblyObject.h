//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - Motor Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_MOTOROUTPUTASSEMBLY_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_MOTOROUTPUTASSEMBLY_H

#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/IOOutputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/MotorOutputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/SerialAsciiOutputData.h"
#include <functional>

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

/**
 * @class MotorOutputAssembly
 *
 * @brief Implements the Step & Direction Motor Output Data section
 */
class MotorOutputAssemblyObject : public BaseAssemblyObject {
public:
  static const eipScanner::cip::CipUint INSTANCE_ID = 0x70;

  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  MotorOutputAssemblyObject(const eipScanner::SessionInfoIf::SPtr sessionInfo,
                           const eipScanner::MessageRouter::SPtr messageRouter);

private:
  std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
  _getAssemblyDataFieldReferences() override;

  // Actual field members
  assembly::output::IOOutputData _ioOutputData;
  assembly::output::MotorOutputData _motor0OutputData;
  assembly::output::MotorOutputData _motor1OutputData;
  assembly::output::MotorOutputData _motor2OutputData;
  assembly::output::MotorOutputData _motor3OutputData;
  assembly::output::SerialAsciiOutputData _serialAsciiOutputData;
};

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_MOTOROUTPUTASSEMBLY_H
