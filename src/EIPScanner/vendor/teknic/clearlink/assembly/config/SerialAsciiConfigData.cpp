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
    : BaseAssemblyData(), _serialBaudRate(), _inputStartDelimiter(),
      _inputEndDelimiter(), _outputStartDelimiter(), _outputEndDelimiter(),
      _inputTimeout() {}

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
