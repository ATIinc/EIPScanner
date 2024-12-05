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

  /**
   * @brief Gets MoveDistance [AttrID=1]
   * @return
   */
  eipScanner::cip::CipDint getMoveDistance() const;

  /**
   * @brief Gets JogVelocity [AttrID=2]
   * @return
   */
  eipScanner::cip::CipDint getJogVelocity() const;

  /**
   * @brief Gets VelocityLimitForPositionalMove [AttrID=3]
   * @return
   */
  eipScanner::cip::CipUdint getVelocityLimit() const;

  /**
   * @brief Gets AccelerationLimitForPositionalMove [AttrID=4]
   * @return
   */
  eipScanner::cip::CipUdint getAccelerationLimit() const;

  /**
   * @brief Gets DecelerationLimit [AttrID=5]
   * @return
   */
  eipScanner::cip::CipUdint getDecelerationLimit() const;

  /**
   * @brief Gets OutputRegister [AttrID=6]
   * @return
   */
  eipScanner::cip::CipDword getOutputRegister() const;

  /**
   * @brief Gets AddToPosition [AttrID=7]
   * @return
   */
  eipScanner::cip::CipDint getAddToPosition() const;

  // -------------------------------------------------------------

  /**
   * @brief Sets MoveDistance [AttrID=1]
   * @return
   */
  void setMoveDistance(eipScanner::cip::CipDint moveDistance);

  /**
   * @brief Sets JogVelocity [AttrID=2]
   * @return
   */
  void setJogVelocity(eipScanner::cip::CipDint jogVelocity);

  /**
   * @brief Sets VelocityLimitForPositionalMove [AttrID=3]
   * @return
   */
  void setVelocityLimit(
      eipScanner::cip::CipUdint velocityLimitForPositionalMove);

  /**
   * @brief Sets AccelerationLimitForPositionalMove [AttrID=4]
   * @return
   */
  void setAccelerationLimit(
      eipScanner::cip::CipUdint accelerationLimitForPositionalMove);

  /**
   * @brief Sets DecelerationLimit [AttrID=5]
   * @return
   */
  void setDecelerationLimit(eipScanner::cip::CipUdint decelerationLimit);

  /**
   * @brief Sets OutputRegister [AttrID=6]
   * @return
   */
  void setOutputRegister(eipScanner::cip::CipDword outputRegister);

  /**
   * @brief Sets AddToPosition [AttrID=7]
   * @return
   */
  void setAddToPosition(eipScanner::cip::CipDint addToPosition);

  enum OutputFlag {
    Enable = 0,
    AbsoluteMove = 1,
    HomingMove = 2,
    LoadPositionMove = 3,
    LoadVelocityMove = 4,
    SoftwareEStop = 5,
    ClearAlerts = 6,
    ClearMotorFault = 7,
    // 8-31 are reserved
  };

  /**
   * @brief Sets a motor flag
   */
  void setOutputRegisterFlag(OutputFlag flag, bool value);

  /**
   * @brief Checks if the motor is controlled to have a specific state
   */
  bool hasFlagSet(OutputFlag flag);

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // Actual field members
  eipScanner::cip::CipDint _moveDistance;
  eipScanner::cip::CipUdint _velocityLimit;
  eipScanner::cip::CipUdint _accelerationLimit;
  eipScanner::cip::CipUdint _decelerationLimit;
  eipScanner::cip::CipDint _jogVelocity;
  eipScanner::cip::CipDint _addToPosition;
  eipScanner::cip::CipDword _outputRegister;
};

} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_OUTPUT_MOTOROUTPUTDATA_H
