//
// Created by Jan Ritzenhoff on 8/29/2024.
//

/* Based on: https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=17
    * GET  : Instance 0x64 - Attribute 3 - Target 2 Originator (Step & Direction Input Assembly)
    * SET  : Instance 0x70 - Attribute 3 - Originator 2 Target (Step & Direction Output Assembly)
    * BOTH : Instance 0x96 - Attribute 3 - Configuration Object (Step & Direction Config Assembly)
    * 
*/

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLYOBJECT_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLYOBJECT_H

#include <variant>
#include <functional>
#include <vector>

#include "EIPScanner/cip/Types.h"
#include "EIPScanner/BaseObject.h"
#include "EIPScanner/SessionInfo.h"
#include "EIPScanner/MessageRouter.h"

#include "EIPScanner/utils/Buffer.h"

namespace eipScanner
{
namespace vendor
{
namespace teknic
{
namespace clearlink
{


    /**
     * @class AssemblyObject
     *
     * @brief Base class for all the CIP Objects that access all attributes independently using explicit messaging
     */
    class AssemblyObject : public eipScanner::BaseObject
    {
    public:
        static const eipScanner::cip::CipUint CLASS_ID = 0x04;

        /**
         * @brief Creates an CIP instance
         * @param instanceId the instance ID of the the new instance
         */
        AssemblyObject(eipScanner::cip::CipUint instanceId, const eipScanner::SessionInfoIf::SPtr sessionInfo, const eipScanner::MessageRouter::SPtr messageRouter);

    protected:
        using ReflexiveObjectFieldReference = std::variant<std::reference_wrapper<eipScanner::cip::CipOctet>,
                                                            std::reference_wrapper<eipScanner::cip::CipBool>,
                                                            std::reference_wrapper<eipScanner::cip::CipByte>,
                                                            std::reference_wrapper<eipScanner::cip::CipWord>,
                                                            std::reference_wrapper<eipScanner::cip::CipDword>,
                                                            std::reference_wrapper<eipScanner::cip::CipUsint>,
                                                            std::reference_wrapper<eipScanner::cip::CipUint>,
                                                            std::reference_wrapper<eipScanner::cip::CipSint>,
                                                            std::reference_wrapper<eipScanner::cip::CipInt>,
                                                            std::reference_wrapper<eipScanner::cip::CipDint>,
                                                            std::reference_wrapper<eipScanner::cip::CipReal>,
                                                            std::reference_wrapper<eipScanner::cip::CipLreal>,
                                                            std::reference_wrapper<eipScanner::cip::CipLword>,
                                                            std::reference_wrapper<eipScanner::cip::CipLint>,
                                                            std::reference_wrapper<eipScanner::cip::CipUlint>>;
        // std::reference_wrapper<eipScanner::cip::CipUdint>, (this is typedeffed' to the same thing as the DWord. Including both in the variant confuses the compiler)

        virtual std::vector<ReflexiveObjectFieldReference> _getAttributeReferences() = 0;

        /**
         * @brief Gets the whole assembly to the device as individual get_attribute_single messages
         */
        void _getAttributes();

        /**
         * @brief Sets the whole assembly to the device as individual set_attribute_single messages
         */
        void _setAttributes();

    private:
        const eipScanner::SessionInfoIf::SPtr _sessionInfo;
        const eipScanner::MessageRouter::SPtr _messageRouter;
    };
}
}
}
}

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLYOBJECT_H
