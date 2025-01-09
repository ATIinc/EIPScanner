//
// Created by Jan Ritzenhoff on 12/4/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/IOInputData.h"
#include "EIPScanner/cip/Types.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {

IOInputData::IOInputData()
    : BaseAssemblyData(), _dipValue(DIP_VALUE_SIZE),
      _dipStatus(DIP_STATUS_SIZE), _aipValue(AIP_VALUE_SIZE),
      _aiopStatus(AIOP_STATUS_SIZE), _dopStatus(DOP_STATUS_SIZE),
      _ccioInputValue(), _ccioStatus(), _ccioBoardCount(),
      _reservedPadding(PADDING_BYTES_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
IOInputData::_getDataFieldReferences() {
  return {std::ref(_dipValue),       std::ref(_dipStatus),
          std::ref(_aipValue),       std::ref(_aiopStatus),
          std::ref(_dopStatus),      std::ref(_ccioInputValue),
          std::ref(_ccioStatus),     std::ref(_ccioBoardCount),
          std::ref(_reservedPadding)};
}

const eipScanner::cip::CipBool
IOInputData::getDigitalInputValue(DigitalInput digitalInput) {
  return _getBitValueFromVector(_dipValue, static_cast<uint8_t>(digitalInput));
}
const eipScanner::cip::CipBool
IOInputData::getDigitalInputStatus(DigitalInput digitalInput) {
  return _getBitValueFromVector(_dipStatus, static_cast<uint8_t>(digitalInput));
}
const eipScanner::cip::CipInt
IOInputData::getAnalogInputValue(AnalogInput analogInput) {
  eipScanner::cip::CipUint unsignedInput = _aipValue.at(static_cast<uint8_t>(analogInput));
  return static_cast<eipScanner::cip::CipInt>(unsignedInput);
}
const eipScanner::cip::CipBool
IOInputData::getAnalogInputStatus(AnalogInput analogInput) {
  return _getBitValueFromVector(_aiopStatus, static_cast<uint8_t>(analogInput));
}
const eipScanner::cip::CipBool
IOInputData::getAnalogOutputStatus(AnalogOutput analogOutput) {
  return _getBitValueFromVector(_aiopStatus,
                                static_cast<uint8_t>(analogOutput));
}

// -------------------------------------------------------------

void IOInputData::setDipValue(
    const std::vector<eipScanner::cip::CipBool> dipValue) {
  // TODO: Add length constraints so that the size of dipValue is always ==
  // _dipValueSize;
  _dipValue = dipValue;
  _dipValue.resize(DIP_VALUE_SIZE);
}

void IOInputData::setDipStatus(
    const std::vector<eipScanner::cip::CipBool> dipStatus) {
  _dipStatus = dipStatus;
  _dipStatus.resize(DIP_STATUS_SIZE);
}

void IOInputData::setAipValue(
    const std::vector<eipScanner::cip::CipUint> aipValue) {
  _aipValue = aipValue;
  _aipValue.resize(AIP_VALUE_SIZE);
}

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
