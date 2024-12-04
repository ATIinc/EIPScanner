//
// Created by Jan Ritzenhoff on 8/28/2024
//
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/SerialAsciiInputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {

SerialAsciiInputData::SerialAsciiInputData()
    : BaseAssemblyData(), _serialStatus(), _outputCharCount(),
      _inputCharCount(), _outputSequenceAck(), _inputSize(), _inputSequence(),
      _inputData(INPUT_DATA_SIZE) {}

std::vector<BaseAssemblyData::DataFieldReference>
SerialAsciiInputData::_getDataFieldReferences() {
  return {std::ref(_serialStatus),   std::ref(_outputCharCount),
          std::ref(_inputCharCount), std::ref(_outputSequenceAck),
          std::ref(_inputSize),      std::ref(_inputSequence),
          std::ref(_inputData)};
}

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner
