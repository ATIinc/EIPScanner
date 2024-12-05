//
// Created by Jan Ritzenhoff on 12/5/2024
//

// Based on:
//	Assembly Object - Motor Output Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=19

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_MOTOROUTPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_MOTOROUTPUTDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {
/**
 * @class MotorOutputData
 *
 * @brief Implements the Step & Direction Motor Output Data section
 */
class MotorOutputData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  MotorOutputData();

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // Actual field members
  eipScanner::cip::CipDint  _moveDistance;
  eipScanner::cip::CipUdint _velocityLimit;
  eipScanner::cip::CipUdint _accelerationLimit;
  eipScanner::cip::CipUdint _decelerationLimit;
  eipScanner::cip::CipDint  _jogVelocity;
  eipScanner::cip::CipDint  _addToPosition;
  eipScanner::cip::CipDword _outputRegister;
};

} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_MOTOROUTPUTDATA_H
