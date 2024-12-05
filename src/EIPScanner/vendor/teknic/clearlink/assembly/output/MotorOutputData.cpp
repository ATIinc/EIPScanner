//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/MotorOutputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {

MotorOutputData::MotorOutputData()
    : BaseAssemblyData(), _moveDistance(), _velocityLimit(),
      _accelerationLimit(), _decelerationLimit(), _jogVelocity(),
      _addToPosition(), _outputRegister() {}

std::vector<BaseAssemblyData::DataFieldReference>
MotorOutputData::_getDataFieldReferences() {
  return {std::ref(_moveDistance),      std::ref(_velocityLimit),
          std::ref(_accelerationLimit), std::ref(_decelerationLimit),
          std::ref(_jogVelocity),       std::ref(_addToPosition),
          std::ref(_outputRegister)};
}

// --------------------------------------------

eipScanner::cip::CipDint MotorOutputData::getMoveDistance() const {
  return _moveDistance;
}
void MotorOutputData::setMoveDistance(eipScanner::cip::CipDint moveDistance) {
  _moveDistance = moveDistance;
}

// --------------------------------------------

eipScanner::cip::CipUdint MotorOutputData::getVelocityLimit() const {
  return _velocityLimit;
}
void MotorOutputData::setVelocityLimit(
    eipScanner::cip::CipUdint velocityLimitForPositionalMove) {
  _velocityLimit = velocityLimitForPositionalMove;
}

// --------------------------------------------

eipScanner::cip::CipUdint MotorOutputData::getAccelerationLimit() const {
  return _accelerationLimit;
}
void MotorOutputData::setAccelerationLimit(
    eipScanner::cip::CipUdint accelerationLimitForPositionalMove) {
  _accelerationLimit = accelerationLimitForPositionalMove;
}

// --------------------------------------------

eipScanner::cip::CipUdint MotorOutputData::getDecelerationLimit() const {
  return _decelerationLimit;
}
void MotorOutputData::setDecelerationLimit(
    eipScanner::cip::CipUdint decelerationLimit) {
  _decelerationLimit = decelerationLimit;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorOutputData::getJogVelocity() const {
  return _jogVelocity;
}
void MotorOutputData::setJogVelocity(eipScanner::cip::CipDint jogVelocity) {
  _jogVelocity = jogVelocity;
}

// --------------------------------------------

eipScanner::cip::CipDint MotorOutputData::getAddToPosition() const {
  return _addToPosition;
}
void MotorOutputData::setAddToPosition(eipScanner::cip::CipDint addToPosition) {
  _addToPosition = addToPosition;
}

// --------------------------------------------

eipScanner::cip::CipDword MotorOutputData::getOutputRegister() const {
  return _outputRegister;
}
bool MotorOutputData::hasFlagSet(OutputFlag flag) {
  return _outputRegister & (0x1 << flag);
}

void MotorOutputData::setOutputRegister(
    eipScanner::cip::CipDword outputRegister) {
  _outputRegister = outputRegister;
}

void MotorOutputData::setOutputRegisterFlag(MotorOutputData::OutputFlag flag,
                                            bool value) {
  if (value) {
    _outputRegister |= (0x1 << flag);
  } else {
    _outputRegister &= ~(0x1 << flag);
  }
}

} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
