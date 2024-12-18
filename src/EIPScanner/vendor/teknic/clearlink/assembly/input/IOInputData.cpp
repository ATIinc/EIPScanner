//
// Created by Jan Ritzenhoff on 12/4/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/IOInputData.h"

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

// -------------------------------------------------------------

const std::vector<eipScanner::cip::CipBool> IOInputData::getDipValue() {
  return _dipValue;
}
const std::vector<eipScanner::cip::CipBool> IOInputData::getDipStatus() {
  return _dipStatus;
}
const std::vector<eipScanner::cip::CipUint> IOInputData::getAipValue() {
  return _aipValue;
}

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
