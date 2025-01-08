//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/IOOutputData.h"
#include <cstdint>

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {

IOOutputData::IOOutputData()
    : BaseAssemblyData(), _aopValue(), _dopValue(DOP_VALUE_SIZE),
      _dopPWM(DOP_PWM_SIZE), _reservedPadding(PADDING_BYTES_SIZE),
      _ccioOutputData(), _encoderAddToPosition() {}

std::vector<BaseAssemblyData::DataFieldReference>
IOOutputData::_getDataFieldReferences() {

  return {std::ref(_aopValue),       std::ref(_dopValue),
          std::ref(_dopPWM),         std::ref(_reservedPadding),
          std::ref(_ccioOutputData), std::ref(_encoderAddToPosition)};
}

// -------------------------------------------------------------

eipScanner::cip::CipInt IOOutputData::getAnalogOutputValue() {
  return _aopValue;
}

void IOOutputData::setAnalogOutputValue(cip::CipInt analogValue) {
  _aopValue = analogValue;
}

// -------------------------------------------------------------

bool IOOutputData::getDigitalOutputValue(DigitalOutput output) {
  // There are only 6 outputs (only need the first byte)
  return _dopValue.at(0) & (1 << static_cast<uint8_t>(output));
}

void IOOutputData::setDigitalOutputValue(DigitalOutput output,
                                         bool outputValue) {

  // special case as this is also an analog pin
  if (output == DigitalOutput::IO_0) {
    setDigitalOutputPWM(output, DEFAULT_PWM_VALUE);
  }

  // There are only 6 outputs (only need the first byte)
  if (outputValue) {
    _dopValue.at(0) |= (0x1 << static_cast<uint8_t>(output));
  } else {
    _dopValue.at(0) &= ~(0x1 << static_cast<uint8_t>(output));
  }
}

// -------------------------------------------------------------

eipScanner::cip::CipUsint
IOOutputData::getDigitalOutputPWM(DigitalOutput output) {
  return _dopPWM.at(static_cast<uint8_t>(output));
}

void IOOutputData::setDigitalOutputPWM(DigitalOutput output,
                                       eipScanner::cip::CipUsint pwmValue) {
  _dopPWM.at(static_cast<uint8_t>(output)) = pwmValue;
}

} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
