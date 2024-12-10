//
// Created by Jan Ritzenhoff on 12/4/2024.
//
#include <functional>
#include <ostream>
// #include <iostream>

#include "EIPScanner/utils/Logger.h"
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

void BaseAssemblyObject::getAssembly() {
  // actually send the explicit message
  auto messagePath = eipScanner::cip::EPath(getClassId(), getInstanceId(),
                                            ASSEMBLY_OBJECT_ATTRIBUTE_ID);

  auto getAssemblyResponse = _messageRouter->sendRequest(
      _sessionInfo, eipScanner::cip::ServiceCodes::GET_ATTRIBUTE_SINGLE,
      messagePath, {});

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

  for (uint fieldIndex = 0; fieldIndex < subAssemblyReferences.size();
       ++fieldIndex) {
    getBuffer >> subAssemblyReferences[fieldIndex];
  }
}

void BaseAssemblyObject::setAssembly() {
  std::vector<std::reference_wrapper<assembly::BaseAssemblyData>>
      subAssemblyReferences = _getAssemblyDataFieldReferences();

  eipScanner::utils::Buffer fullAssemblyBuffer;

  for (uint fieldIndex = 0; fieldIndex < subAssemblyReferences.size();
       ++fieldIndex) {
    fullAssemblyBuffer << subAssemblyReferences[fieldIndex];
  }

  // actually send the explicit message
  auto messagePath = eipScanner::cip::EPath(getClassId(), getInstanceId(),
                                            ASSEMBLY_OBJECT_ATTRIBUTE_ID);

  auto setAttributeResponse = _messageRouter->sendRequest(
      _sessionInfo, eipScanner::cip::ServiceCodes::SET_ATTRIBUTE_SINGLE,
      messagePath, fullAssemblyBuffer.data());

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