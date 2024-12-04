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
    eipScanner::utils::Buffer& operator<<(eipScanner::utils::Buffer& outStream, const BaseAssemblyData& assemblyData)
    {
        outStream << 0x1;
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