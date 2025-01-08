//
// Created by Jan Ritzenhoff on 12/4/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/MotorInputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {

MotorInputData::MotorInputData()
    : BaseAssemblyData(), _commandedPosition(), _commandedVelocity(),
      _targetPosition(), _targetVelocity(), _capturedPosition(),
      _measuredTorque(), _motorStatus(), _motorShutdowns() {}

std::vector<BaseAssemblyData::DataFieldReference>
MotorInputData::_getDataFieldReferences() {
  return {std::ref(_commandedPosition), std::ref(_commandedVelocity),
          std::ref(_targetPosition),    std::ref(_targetVelocity),
          std::ref(_capturedPosition),  std::ref(_measuredTorque),
          std::ref(_motorStatus),       std::ref(_motorShutdowns)};
}

// --------------------------------------------

eipScanner::cip::CipDint MotorInputData::getCommandedPosition() const {
  return _commandedPosition;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorInputData::getCommandedVelocity() const {
  return _commandedVelocity;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorInputData::getTargetPosition() const {
  return _targetPosition;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorInputData::getTargetVelocity() const {
  return _targetVelocity;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorInputData::getCapturedPosition() const {
  return _capturedPosition;
}

// --------------------------------------------

eipScanner::cip::CipReal MotorInputData::getMeasuredTorque() const {
  return _measuredTorque;
}

// --------------------------------------------

eipScanner::cip::CipDword MotorInputData::getMotorStatus() const {
  return _motorStatus;
}

// --------------------------------------------

eipScanner::cip::CipDword MotorInputData::getMotorShutdowns() const {
  return _motorShutdowns;
}

// --------------------------------------------

bool MotorInputData::hasMotorStatus(MotorStatus specificStatus) {
  return _motorStatus & (0x1 << static_cast<uint8_t>(specificStatus));
}

std::string MotorInputData::motorStatusToString(MotorStatus specificStatus) {
  switch (specificStatus) {
  case MotorStatus::AtTargetPosition:
    return "AtTargetPosition";
  case MotorStatus::StepsActive:
    return "StepsActive";
  case MotorStatus::AtVelocity:
    return "AtVelocity";
  case MotorStatus::MoveDirection:
    return "MoveDirection";
  case MotorStatus::InPositiveLimit:
    return "InPositiveLimit";
  case MotorStatus::InNegativeLimit:
    return "InNegativeLimit";
  case MotorStatus::InEStopSensor:
    return "InEStopSensor";
  case MotorStatus::InHomeSensor:
    return "InHomeSensor";
  case MotorStatus::Homing:
    return "Homing";
  case MotorStatus::MotorInFault:
    return "MotorInFault";
  case MotorStatus::Enabled:
    return "Enabled";
  case MotorStatus::OutsideSoftLimits:
    return "OutsideSoftLimits";
  case MotorStatus::PositionalMove:
    return "PositionalMove";
  case MotorStatus::HasHomed:
    return "HasHomed";
  case MotorStatus::HLFB_On:
    return "HLFB_On";
  case MotorStatus::HasTorqueMeasurement:
    return "HasTorqueMeasurement";
  case MotorStatus::ReadyToHome:
    return "ReadyToHome";
  case MotorStatus::ShutdownsPresent:
    return "ShutdownsPresent";
  case MotorStatus::AddToPositionAck:
    return "AddToPositionAck";
  case MotorStatus::LoadPositionMoveAck:
    return "LoadPositionMoveAck";
  case MotorStatus::LoadVelocityMoveAck:
    return "LoadVelocityMoveAck";
  case MotorStatus::ClearMotorFaultAck:
    return "ClearMotorFaultAck";
  default:
    return "Unknown State";
  }
}

// --------------------------------------------

bool MotorInputData::hasMotorShutdown(MotorShutdown specificShutdown) {
  return _motorShutdowns & (0x1 << static_cast<uint8_t>(specificShutdown));
}

std::string
MotorInputData::motorShutdownToString(MotorShutdown specificShutdown) {
  switch (specificShutdown) {

  case MotorShutdown::MotionCanceled_CommandWhileShutdown:
    return "MotionCanceled_CommandWhileShutdown";
  case MotorShutdown::MotionCanceled_PosLimit:
    return "MotionCanceled_PosLimit";
  case MotorShutdown::MotionCanceled_NegLimit:
    return "MotionCanceled_NegLimit";
  case MotorShutdown::MotionCanceled_SensorEStop:
    return "MotionCanceled_SensorEStop";
  case MotorShutdown::MotionCanceled_SoftwareEStop:
    return "MotionCanceled_SoftwareEStop";
  case MotorShutdown::MotionCanceled_MotorDisabled:
    return "MotionCanceled_MotorDisabled";
  case MotorShutdown::MotionCanceled_SoftLimitExceeded:
    return "MotionCanceled_SoftLimitExceeded";
  case MotorShutdown::MotionCanceled_FollowerAxisFault:
    return "MotionCanceled_FollowerAxisFault";
  case MotorShutdown::MotionCanceled_CommandWhileFollowing:
    return "MotionCanceled_CommandWhileFollowing";
  case MotorShutdown::MotionCanceled_HomingNotReady:
    return "MotionCanceled_HomingNotReady";
  case MotorShutdown::MotorFaulted:
    return "MotorFaulted";
  case MotorShutdown::FollowingOverspeed:
    return "FollowingOverspeed";
  default:
    return "Unknown State"; // 13 - 31 are reserved;
  }
}

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
