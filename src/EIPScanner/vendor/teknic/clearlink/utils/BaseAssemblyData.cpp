#include "EIPScanner/vendor/teknic/clearlink/utils/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace utils {

BaseAssemblyData::BaseAssemblyData() {}

// NOT a part of the class
eipScanner::utils::Buffer &operator<<(eipScanner::utils::Buffer &outStream,
                                      BaseAssemblyData &assemblyData) {
  std::vector<BaseAssemblyData::ReflexiveFieldReference> classAttributes =
      assemblyData._getAttributeReferences();

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
  std::vector<BaseAssemblyData::ReflexiveFieldReference> classAttributes =
      assemblyData._getAttributeReferences();

  for (uint8_t fieldIndex = 0; fieldIndex < classAttributes.size();
       ++fieldIndex) {
    auto fieldReference = classAttributes[fieldIndex];

    // pass a reference of the getBuffer to the lambda function and the first
    // argument of the lambda function is the actual field reference
    std::visit([&inStream](auto &fieldRef) { inStream >> fieldRef; },
               fieldReference);
  }

  return inStream;
}

} // namespace utils
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner