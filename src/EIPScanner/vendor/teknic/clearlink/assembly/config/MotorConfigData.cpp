//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/MotorConfigData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {

MotorConfigData::MotorConfigData()
    : BaseAssemblyData(), _configRegister(DEFAULT_CONFIG_REGISTER_VALUE),
      _followDivisor(DEFAULT_FOLLOW_DIVISOR_VALUE),
      _followMultiplier(DEFAULT_FOLLOW_MULTIPLIER_VALUE),
      _maxDeceleration(DEFAULT_MAX_DECELERATION_VALUE),
      _softLimitPosition1(DEFAULT_SOFT_LIMIT_1_VALUE),
      _softLimitPosition2(DEFAULT_SOFT_LIMIT_2_VALUE),
      _positiveLimitConnector(DEFAULT_POSITIVE_LIMIT_CONNECTOR_VALUE),
      _negativeLimitConnector(DEFAULT_NEGATIVE_LIMIT_CONNECTOR_VALUE),
      _homeSensorConnector(DEFAULT_HOME_SENSOR_CONNECTOR_VALUE),
      _brakeOutputConnector(DEFAULT_BRAKE_OUTPUT_CONNECTOR_VALUE),
      _stopSensorConnector(DEFAULT_STOP_SENSOR_CONNECTOR_VALUE),
      _triggerPositionCaptureConnector(
          DEFAULT_TRIGGER_POSITION_CAPTURE_CONNECTOR_VALUE),
      _followAxis(DEFAULT_FOLLOW_AXIS_VALUE),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
MotorConfigData::_getDataFieldReferences() {
  return {std::ref(_configRegister),
          std::ref(_followDivisor),
          std::ref(_followMultiplier),
          std::ref(_maxDeceleration),
          std::ref(_softLimitPosition1),
          std::ref(_softLimitPosition2),
          std::ref(_positiveLimitConnector),
          std::ref(_negativeLimitConnector),
          std::ref(_homeSensorConnector),
          std::ref(_brakeOutputConnector),
          std::ref(_stopSensorConnector),
          std::ref(_triggerPositionCaptureConnector),
          std::ref(_followAxis),
          std::ref(_reservedPadding)};
}

// --------------------------------------------

eipScanner::cip::CipDword MotorConfigData::getConfigRegister() const {
  return _configRegister;
}

void MotorConfigData::setConfigRegisterFlag(ConfigFlag flag, bool value) {
  if (value) {
    _configRegister |= (1 << flag);
  } else {
    _configRegister &= ~(1 << flag);
  }
}

void MotorConfigData::setConfigRegister(
    eipScanner::cip::CipDword configRegister) {
  _configRegister = configRegister;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorConfigData::getFollowDivisor() const {
  return _followDivisor;
}
void MotorConfigData::setFollowDivisor(eipScanner::cip::CipDint followDivisor) {
  _followDivisor = followDivisor;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorConfigData::getFollowMultiplier() const {
  return _followMultiplier;
}
void MotorConfigData::setFollowMultiplier(
    eipScanner::cip::CipDint followMultiplier) {
  _followMultiplier = followMultiplier;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorConfigData::getMaxDeceleration() const {
  return _maxDeceleration;
}
void MotorConfigData::setMaxDeceleration(
    eipScanner::cip::CipDint maxDecelerationRate) {
  _maxDeceleration = maxDecelerationRate;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorConfigData::getSoftLimitPosition1() const {
  return _softLimitPosition1;
}
void MotorConfigData::setSoftLimitPosition1(
    eipScanner::cip::CipDint softLimitPosition1) {
  _softLimitPosition1 = softLimitPosition1;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorConfigData::getSoftLimitPosition2() const {
  return _softLimitPosition2;
}
void MotorConfigData::setSoftLimitPosition2(
    eipScanner::cip::CipDint softLimitPosition2) {
  _softLimitPosition2 = softLimitPosition2;
}

// --------------------------------------------

eipScanner::cip::CipSint MotorConfigData::getPositiveLimitConnector() const {
  return _positiveLimitConnector;
}
void MotorConfigData::setPositiveLimitConnector(
    eipScanner::cip::CipSint positiveLimitConnector) {
  _positiveLimitConnector = positiveLimitConnector;
}

// --------------------------------------------

eipScanner::cip::CipSint MotorConfigData::getNegativeLimitConnector() const {
  return _negativeLimitConnector;
}
void MotorConfigData::setNegativeLimitConnector(
    eipScanner::cip::CipSint negativeLimitConnector) {
  _negativeLimitConnector = negativeLimitConnector;
}

// --------------------------------------------

eipScanner::cip::CipSint MotorConfigData::getHomeSensorConnector() const {
  return _homeSensorConnector;
}
void MotorConfigData::setHomeSensorConnector(
    eipScanner::cip::CipSint homeSensorConnector) {
  _homeSensorConnector = homeSensorConnector;
}

// --------------------------------------------

eipScanner::cip::CipSint MotorConfigData::getBrakeOutputConnector() const {
  return _brakeOutputConnector;
}
void MotorConfigData::setBrakeOutputConnector(
    eipScanner::cip::CipSint brakeOutputConnector) {
  _brakeOutputConnector = brakeOutputConnector;
}

// --------------------------------------------

eipScanner::cip::CipSint MotorConfigData::getStopSensorConnector() const {
  return _stopSensorConnector;
}
void MotorConfigData::setStopSensorConnector(
    eipScanner::cip::CipSint stopSensorConnector) {
  _stopSensorConnector = stopSensorConnector;
}

// --------------------------------------------

eipScanner::cip::CipSint
MotorConfigData::getTriggerPositionCaptureConnector() const {
  return _triggerPositionCaptureConnector;
}
void MotorConfigData::setTriggerPositionCaptureConnector(
    eipScanner::cip::CipSint triggerPositionCaptureConnector) {
  _triggerPositionCaptureConnector = triggerPositionCaptureConnector;
}

// --------------------------------------------

eipScanner::cip::CipSint MotorConfigData::getFollowAxis() const {
  return _followAxis;
}
void MotorConfigData::setFollowAxis(
    eipScanner::cip::CipSint followEncoderMode) {
  _followAxis = followEncoderMode;
}

} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
