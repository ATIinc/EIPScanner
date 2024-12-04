//
// Created by Jan Ritzenhoff on 8/29/2024.
//

#include "EIPScanner/vendor/teknic/clearlink/BaseAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {

BaseAssemblyObject::BaseAssemblyObject(
    eipScanner::cip::CipUint instanceId,
    const eipScanner::SessionInfoIf::SPtr sessionInfo,
    const eipScanner::MessageRouter::SPtr messageRouter)
    : BaseObject(CLASS_ID, instanceId), _sessionInfo(sessionInfo),
      _messageRouter(messageRouter) {}

void BaseAssemblyObject::_getAttribute() {
  // actually send the explicit message
  auto getAssemblyResponse = _messageRouter->sendRequest(
      _sessionInfo, eipScanner::cip::ServiceCodes::GET_ATTRIBUTE_SINGLE,
      eipScanner::cip::EPath(getClassId(), getInstanceId(),
                             ASSEMBLY_OBJECT_ATTRIBUTE_ID));

  if (getAssemblyResponse.getGeneralStatusCode() !=
      eipScanner::cip::GeneralStatusCodes::SUCCESS) {
    logGeneralAndAdditionalStatus(getAssemblyResponse);
    throw std::runtime_error(
        "Failed to read attribute with status code: " +
        std::to_string(getAssemblyResponse.getGeneralStatusCode()));
  }

  eipScanner::utils::Buffer getBuffer(getAssemblyResponse.getData());

  std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
      subAssemblyReferences = _getAssemblyDataFieldReferences();
  for (auto fieldReference : subAssemblyReferences) {
    getBuffer >> fieldReference;
  }
}

void BaseAssemblyObject::_setAttribute() {
  std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
      subAssemblyReferences = _getAssemblyDataFieldReferences();

  eipScanner::utils::Buffer fullAssemblyBuffer;

  for (auto fieldReference : subAssemblyReferences) {
    fullAssemblyBuffer << fieldReference;
  }

  // actually send the explicit message
  auto setAttributeResponse = _messageRouter->sendRequest(
      _sessionInfo, eipScanner::cip::ServiceCodes::SET_ATTRIBUTE_SINGLE,
      eipScanner::cip::EPath(getClassId(), getInstanceId()),
      fullAssemblyBuffer.data());

  // check the setAttributeResponse code
  if (setAttributeResponse.getGeneralStatusCode() !=
      eipScanner::cip::GeneralStatusCodes::SUCCESS) {
    logGeneralAndAdditionalStatus(setAttributeResponse);
    throw std::runtime_error(
        "Failed to read attribute with status code: " +
        std::to_string(setAttributeResponse.getGeneralStatusCode()));
  }
}

} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner