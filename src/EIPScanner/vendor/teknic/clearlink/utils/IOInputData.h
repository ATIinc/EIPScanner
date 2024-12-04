//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - IO Input Data (04hex - 1 instance)
//		* https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_UTILS_IOINPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_UTILS_IOINPUTDATA_H

#include "EIPScanner/cip/Types.h"

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
    /**
     * @class IOInputData
     *
     * @brief Implements the Step & Direction IO Input Data section
     */
    class IOInputData : public BaseAssemblyData
    {
    public:

        /**
         * @brief Creates an instance that reads a buffer
         * @param data
         */
        IOInputData();

        // -------------------------------------------------------------

        void setDipValue(const std::vector<eipScanner::cip::CipBool> dipValue);
        void setDipStatus(const eipScanner::cip::CipDint dipStatus);
        void setAipValue(const eipScanner::cip::CipDint aipValue);

        // -------------------------------------------------------------

        const std::vector<eipScanner::cip::CipBool>  getDipValue();
        const eipScanner::cip::CipDint getDipStatus();
        const eipScanner::cip::CipDint getAipValue();

    private:
        virtual std::vector<ReflexiveFieldReference> _getAttributeReferences();

        // CONSTANTS
        size_t _dipValueSize = 13;


        std::vector<eipScanner::cip::CipBool> _dipValue; // needs to be of size 13
        eipScanner::cip::CipDint _dipStatus;
        eipScanner::cip::CipDint _aipValue;
    };
}
}
}
}
}


#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_UTILS_IOINPUTDATA_H
