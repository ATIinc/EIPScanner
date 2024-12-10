//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/SerialAsciiConfigData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace config {

SerialAsciiConfigData::SerialAsciiConfigData()
    : BaseAssemblyData(), _serialBaudRate(DEFAULT_SERIAL_BAUD_RATE_VALUE),
      _inputStartDelimiter(DEFAULT_INPUT_START_DELIMITER_VALUE),
      _inputEndDelimiter(DEFAULT_INPUT_END_DELIMITER_VALUE),
      _outputStartDelimiter(DEFAULT_OUTPUT_START_DELIMITER_VALUE),
      _outputEndDelimiter(DEFAULT_OUTPUT_END_DELIMITER_VALUE),
      _inputTimeout(DEFAULT_INTPUT_TIMEOUT_VALUE) {}

std::vector<BaseAssemblyData::DataFieldReference>
SerialAsciiConfigData::_getDataFieldReferences() {
  return {std::ref(_serialBaudRate),     std::ref(_inputStartDelimiter),
          std::ref(_inputEndDelimiter),  std::ref(_outputStartDelimiter),
          std::ref(_outputEndDelimiter), std::ref(_inputTimeout)};
}
} // namespace config
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
