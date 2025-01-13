//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/IOModeConfigData.h"
#include "EIPScanner/cip/Types.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {

IOModeConfigData::IOModeConfigData()
    : BaseAssemblyData(), _aI0Range(DEFAULT_AI0_RANGE_VALUE),
      _aI1Range(DEFAULT_AI1_RANGE_VALUE), _aI2Range(DEFAULT_AI2_RANGE_VALUE),
      _aI3Range(DEFAULT_AI3_RANGE_VALUE), _aO0Range(DEFAULT_AO0_RANGE_VALUE),
      _dopPWMFrequency(DEFAULT_PWM_FREQUENCY), _ccioEnable(DEFAULT_CCIO_ENABLE),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
IOModeConfigData::_getDataFieldReferences() {

  return {std::ref(_aI0Range),   std::ref(_aI1Range),
          std::ref(_aI2Range),   std::ref(_aI3Range),
          std::ref(_aO0Range),   std::ref(_dopPWMFrequency),
          std::ref(_ccioEnable), std::ref(_reservedPadding)};
}

eipScanner::cip::CipUsint IOModeConfigData::getAI0Range() { return _aI0Range; }

void IOModeConfigData::setAI0Range(AnalogInputRange analogInput0Range) {
  _aI0Range = static_cast<cip::CipUsint>(analogInput0Range);
}

// -------------------------------------------------------------

eipScanner::cip::CipUsint IOModeConfigData::getAI1Range() { return _aI1Range; }

void IOModeConfigData::setAI1Range(AnalogInputRange analogInput1Range) {
  _aI1Range = static_cast<cip::CipUsint>(analogInput1Range);
}

// -------------------------------------------------------------

eipScanner::cip::CipUsint IOModeConfigData::getAI2Range() { return _aI2Range; }

void IOModeConfigData::setAI2Range(AnalogInputRange analogInput2Range) {
  _aI2Range = static_cast<cip::CipUsint>(analogInput2Range);
}

// -------------------------------------------------------------

eipScanner::cip::CipUsint IOModeConfigData::getAI3Range() { return _aI3Range; }

void IOModeConfigData::setAI3Range(AnalogInputRange analogInput3Range) {
  _aI3Range = static_cast<cip::CipUsint>(analogInput3Range);
}

// -------------------------------------------------------------

eipScanner::cip::CipUsint IOModeConfigData::getAO0Range() { return _aO0Range; }

void IOModeConfigData::setAO0Range(AnalogOutputRange analogOutput0Range) {
  _aO0Range = static_cast<cip::CipUsint>(analogOutput0Range);
}

// -------------------------------------------------------------

eipScanner::cip::CipBool IOModeConfigData::getDopPWMFrequency() {
  return _dopPWMFrequency;
}

void IOModeConfigData::setDopPWMFrequency(PWMFrequency dopPWMFrequency) {
  _dopPWMFrequency = static_cast<cip::CipBool>(dopPWMFrequency);
}

} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
