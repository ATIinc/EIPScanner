//
// Created by Jan Ritzenhoff on 12/4/2024.
//

/* Based on:
 * https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=17
 *
 * GET  : Instance 0x64 - Attribute 3 - Target 2 Originator (Step & Direction Input Assembly)
 *
 * SET  : Instance 0x70 - Attribute 3 - Originator 2 Target (Step & Direction Output Assembly) 
 * 
 * BOTH : Instance 0x96 - Attribute 3 - Configuration Object (Step & Direction Config Assembly)
 */

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_BASEASSEMBLYOBJECT_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_BASEASSEMBLYOBJECT_H

#include <functional>
#include <vector>

#include "EIPScanner/BaseObject.h"
#include "EIPScanner/MessageRouter.h"
#include "EIPScanner/SessionInfo.h"
#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

/**
 * @class BaseAssemblyObject
 *
 * @brief Base class for all the CIP Objects that access all attributes
 * independently using explicit messaging
 */
class BaseAssemblyObject : public eipScanner::BaseObject {
public:
  static const eipScanner::cip::CipUint CLASS_ID = 0x04;
  static const uint8_t ASSEMBLY_OBJECT_ATTRIBUTE_ID = 0x3;

  /**
   * @brief Creates an CIP instance
   * @param instanceId the instance ID of the the new instance
   */
  BaseAssemblyObject(eipScanner::cip::CipUint instanceId,
                     const eipScanner::SessionInfoIf::SPtr sessionInfo,
                     const eipScanner::MessageRouter::SPtr messageRouter);

  /**
   * @brief Gets the whole assembly
   */
  void getAssembly();

  /**
   * @brief Sets the whole assembly
   */
  void setAssembly();

protected:
  virtual std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
  _getAssemblyDataFieldReferences() = 0;

private:
  const eipScanner::SessionInfoIf::SPtr _sessionInfo;
  const eipScanner::MessageRouter::SPtr _messageRouter;
};
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_BASEASSEMBLYOBJECT_H
