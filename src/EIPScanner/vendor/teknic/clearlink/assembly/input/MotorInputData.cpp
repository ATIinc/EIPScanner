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

bool MotorInputData::isInMotorState(InputState state) {
  return _motorStatus & (1 << state);
}

std::string
MotorInputData::motorStateToString(MotorInputData::InputState state) {
  switch (state) {
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
  case NUM_STATES:
    return "NUM_STATES";
  default:
    return "Unknown State";
  }
}

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
