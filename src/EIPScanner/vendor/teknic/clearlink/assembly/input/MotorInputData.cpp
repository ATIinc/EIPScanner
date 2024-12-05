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
  return _motorStatus & (0x1 << specificStatus);
}

std::string MotorInputData::motorStatusToString(MotorStatus specificStatus) {
  switch (specificStatus) {
  case AtTargetPosition:
    return "AtTargetPosition";
  case StepsActive:
    return "StepsActive";
  case AtVelocity:
    return "AtVelocity";
  case MoveDirection:
    return "MoveDirection";
  case InPositiveLimit:
    return "InPositiveLimit";
  case InNegativeLimit:
    return "InNegativeLimit";
  case InEStopSensor:
    return "InEStopSensor";
  case InHomeSensor:
    return "InHomeSensor";
  case Homing:
    return "Homing";
  case MotorInFault:
    return "MotorInFault";
  case Enabled:
    return "Enabled";
  case OutsideSoftLimits:
    return "OutsideSoftLimits";
  case PositionalMove:
    return "PositionalMove";
  case HasHomed:
    return "HasHomed";
  case HLFB_On:
    return "HLFB_On";
  case HasTorqueMeasurement:
    return "HasTorqueMeasurement";
  case ReadyToHome:
    return "ReadyToHome";
  case ShutdownsPresent:
    return "ShutdownsPresent";
  case AddToPositionAck:
    return "AddToPositionAck";
  case LoadPositionMoveAck:
    return "LoadPositionMoveAck";
  case LoadVelocityMoveAck:
    return "LoadVelocityMoveAck";
  case ClearMotorFaultAck:
    return "ClearMotorFaultAck";
  default:
    return "Unknown State";
  }
}

// --------------------------------------------

bool MotorInputData::hasMotorShutdown(MotorShutdown specificShutdown) {
  return _motorShutdowns & (0x1 << specificShutdown);
}

std::string
MotorInputData::motorShutdownToString(MotorShutdown specificShutdown) {
  switch (specificShutdown) {

  case MotionCanceled_CommandWhileShutdown:
    return "MotionCanceled_CommandWhileShutdown";
  case MotionCanceled_PosLimit:
    return "MotionCanceled_PosLimit";
  case MotionCanceled_NegLimit:
    return "MotionCanceled_NegLimit";
  case MotionCanceled_SensorEStop:
    return "MotionCanceled_SensorEStop";
  case MotionCanceled_SoftwareEStop:
    return "MotionCanceled_SoftwareEStop";
  case MotionCanceled_MotorDisabled:
    return "MotionCanceled_MotorDisabled";
  case MotionCanceled_SoftLimitExceeded:
    return "MotionCanceled_SoftLimitExceeded";
  case MotionCanceled_FollowerAxisFault:
    return "MotionCanceled_FollowerAxisFault";
  case MotionCanceled_CommandWhileFollowing:
    return "MotionCanceled_CommandWhileFollowing";
  case MotionCanceled_HomingNotReady:
    return "MotionCanceled_HomingNotReady";
  case MotorFaulted:
    return "MotorFaulted";
  case FollowingOverspeed:
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
