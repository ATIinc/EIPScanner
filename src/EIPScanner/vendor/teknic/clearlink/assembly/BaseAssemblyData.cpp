#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {

BaseAssemblyData::BaseAssemblyData() {}

// NOT a part of the class
eipScanner::utils::Buffer &operator<<(eipScanner::utils::Buffer &outStream,
                                      BaseAssemblyData &assemblyData) {
  std::vector<BaseAssemblyData::DataFieldReference> classAttributes =
      assemblyData._getDataFieldReferences();

  for (uint8_t fieldIndex = 0; fieldIndex < classAttributes.size();
       ++fieldIndex) {

    auto fieldReference = classAttributes[fieldIndex];

    // pass a reference of the buffer to the lambda function
    std::visit([&outStream](auto &fieldRef) { outStream << fieldRef; },
               fieldReference);
  }

  return outStream;
}

eipScanner::utils::Buffer &operator>>(eipScanner::utils::Buffer &inStream,
                                      BaseAssemblyData &assemblyData) {
  std::vector<BaseAssemblyData::DataFieldReference> classAttributes =
      assemblyData._getDataFieldReferences();

  for (uint8_t fieldIndex = 0; fieldIndex < classAttributes.size();
       ++fieldIndex) {
    auto fieldReference = classAttributes[fieldIndex];

    // pass a reference of the inStream to the lambda function and the first
    // argument of the lambda function is the actual field reference
    std::visit([&inStream](auto &fieldRef) { inStream >> fieldRef; },
               fieldReference);
  }

  return inStream;
}

} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner