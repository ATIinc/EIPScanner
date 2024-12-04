//
// Created by Jan Ritzenhoff on 8/28/2024
//
#include "EIPScanner/vendor/teknic/clearlink/utils/IOInputData.h"

#include "EIPScanner/utils/Buffer.h"

#include <type_traits>

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
    IOInputData::IOInputData() : BaseAssemblyData()
    {
    }

    std::vector<BaseAssemblyData::ReflexiveFieldReference> IOInputData::_getAttributeReferences()
    {
        return {std::ref(_dipValue), std::ref(_dipStatus), std::ref(_aipValue)};
    }

    void IOInputData::setDipValue(const std::vector<eipScanner::cip::CipBool>& dipValue) 
    { 
        // TODO: Add length constraints so that the size of dipValue is always == _dipValueSize;
        _dipValue = dipValue;
    }
    void IOInputData::setDipStatus(const eipScanner::cip::CipDint& dipStatus) { _dipStatus = dipStatus; }
    void IOInputData::setAipValue(const eipScanner::cip::CipDint& aipValue) { _aipValue = aipValue; }
}
}
}
}
}
