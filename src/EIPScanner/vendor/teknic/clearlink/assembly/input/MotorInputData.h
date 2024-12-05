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

  /**
   * @brief Gets CommandedPosition [AttrID=1]
   * @return
   */
  eipScanner::cip::CipDint getCommandedPosition() const;

  /**
   * @brief Gets CommandedVelocity [AttrID=2]
   * @return
   */
  eipScanner::cip::CipDint getCommandedVelocity() const;

  /**
   * @brief Gets TargetPosition [AttrID=3]
   * @return
   */
  eipScanner::cip::CipDint getTargetPosition() const;

  /**
   * @brief Gets TargetVelocity [AttrID=4]
   * @return
   */
  eipScanner::cip::CipDint getTargetVelocity() const;

  /**
   * @brief Gets CapturedPosition [AttrID=5]
   * @return
   */
  eipScanner::cip::CipDint getCapturedPosition() const;

  /**
   * @brief Gets MeasuredTorque [AttrID=6]
   * @return
   */
  eipScanner::cip::CipReal getMeasuredTorque() const;

  /**
   * @brief Gets MotorStatus [AttrID=7]
   * @return
   */
  eipScanner::cip::CipDword getMotorStatus() const;

  enum MotorStatus {
    AtTargetPosition = 0,
    StepsActive = 1,
    AtVelocity = 2,
    MoveDirection = 3,
    InPositiveLimit = 4,
    InNegativeLimit = 5,
    InEStopSensor = 6,
    InHomeSensor = 7,
    Homing = 8,
    MotorInFault = 9,
    Enabled = 10,
    OutsideSoftLimits = 11,
    PositionalMove = 12,
    HasHomed = 13,
    HLFB_On = 14,
    HasTorqueMeasurement = 15,
    ReadyToHome = 16,
    ShutdownsPresent = 17,
    AddToPositionAck = 18,
    LoadPositionMoveAck = 19,
    LoadVelocityMoveAck = 20,
    ClearMotorFaultAck = 21,
    NUM_STATES = 22
    // 22 - 31 are reserved
  };

  /**
   * @brief Checks if the motor has a specific status
   */
  bool hasMotorStatus(MotorStatus specificStatus);

  /**
   * @brief Gets MotorShutdowns [AttrID=8]
   * @return
   */
  eipScanner::cip::CipDword getMotorShutdowns() const;

  enum MotorShutdown {
    MotionCanceled_CommandWhileShutdown = 0,
    MotionCanceled_PosLimit = 1,
    MotionCanceled_NegLimit = 2,
    MotionCanceled_SensorEStop = 3,
    MotionCanceled_SoftwareEStop = 4,
    MotionCanceled_MotorDisabled = 5,
    MotionCanceled_SoftLimitExceeded = 6,
    MotionCanceled_FollowerAxisFault = 7,
    MotionCanceled_CommandWhileFollowing = 8,
    MotionCanceled_HomingNotReady = 9,
    MotorFaulted = 10,
    FollowingOverspeed = 11,
    NUM_SHUTDOWNS = 12
    // 13 - 31 are reserved
  };

  /**
   * @brief Checks if the motor has a specific shutdown
   */
  bool hasMotorShutdown(MotorShutdown specificShutdown);

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  // CONSTANTS
  static const size_t ENCODER_STATUS_SIZE = 1; // 2 bits
  static const size_t PADDING_BYTES_SIZE = 2;

  // Actual field members
  eipScanner::cip::CipDint _commandedPosition;
  eipScanner::cip::CipDint _commandedVelocity;
  eipScanner::cip::CipDint _targetPosition;
  eipScanner::cip::CipDint _targetVelocity;
  eipScanner::cip::CipDint _capturedPosition;
  eipScanner::cip::CipReal _measuredTorque;
  eipScanner::cip::CipDword _motorStatus;
  eipScanner::cip::CipDword _motorShutdowns;

  std::string motorStatusToString(MotorStatus specificStatus);
  std::string motorShutdownToString(MotorShutdown specificShutdown);
};

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_MOTORINPUTDATA_H
