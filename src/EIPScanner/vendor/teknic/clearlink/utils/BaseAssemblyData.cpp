#include "EIPScanner/vendor/teknic/clearlink/utils/BaseAssemblyData.h"

namespace eipScanner
{
namespace vendor
{
namespace teknic
{
namespace clearlink
{
namespace utils
{

    BaseAssemblyData::BaseAssemblyData() {}

    // NOT a part of the class
    eipScanner::utils::Buffer& operator<<(eipScanner::utils::Buffer& outStream, BaseAssemblyData& assemblyData)
    {
        std::vector<BaseAssemblyData::ReflexiveFieldReference> classAttributes = assemblyData._getAttributeReferences();

        for (uint8_t fieldIndex = 0; fieldIndex < classAttributes.size(); ++fieldIndex)
        {

            auto fieldReference = classAttributes[fieldIndex];

            // pass a reference of the buffer to the lambda function
            std::visit([&outStream](auto &fieldRef)
                       { outStream << fieldRef; },
                       fieldReference);

        }

        return outStream;
    }

    BaseAssemblyData& BaseAssemblyData::operator>>(eipScanner::utils::Buffer& inStream)
    {
        return *this;
    }

}
}
}
}
}