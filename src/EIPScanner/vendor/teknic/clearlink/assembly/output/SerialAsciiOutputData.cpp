//
// Created by Jan Ritzenhoff on 12/5/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/SerialAsciiOutputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace output {

SerialAsciiOutputData::SerialAsciiOutputData()
    : BaseAssemblyData(), _serialConfig(), _inputSequenceAck(), _outputSize(),
      _outputSequence(), _outputData(OUTPUT_DATA_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
SerialAsciiOutputData::_getDataFieldReferences() {

  return {std::ref(_serialConfig), std::ref(_inputSequenceAck),
          std::ref(_outputSize), std::ref(_outputSequence),
          std::ref(_outputData)};
}

} // namespace output
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
