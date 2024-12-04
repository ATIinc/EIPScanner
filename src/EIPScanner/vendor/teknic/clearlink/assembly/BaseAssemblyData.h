//
// Created by Jan Ritzenhoff on 8/29/2024.
//

/* Based on IO Input Data:
 * https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18
 */

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_BASEASSEMBLYDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_BASEASSEMBLYDATA_H

#include <functional>
#include <variant>
#include <vector>

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/utils/Buffer.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {

/**
 * @class Base Assembly Data
 *
 * @brief Base class for all the clearlink Assembly Data components
 */
class BaseAssemblyData {
public:
  /**
   * @brief Creates a instance
   */
  BaseAssemblyData();

protected:
  using DataFieldReference = std::variant<
      std::reference_wrapper<eipScanner::cip::CipOctet>,
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
      // std::reference_wrapper<eipScanner::cip::CipLword>,
      std::reference_wrapper<eipScanner::cip::CipLint>,
      std::reference_wrapper<eipScanner::cip::CipUlint>,
      std::reference_wrapper<std::vector<eipScanner::cip::CipBool>>,
      std::reference_wrapper<std::vector<eipScanner::cip::CipUint>>>;
  // std::reference_wrapper<eipScanner::cip::CipUdint>, (this is typedeffed' to
  // the same thing as the DWord. Including both in the variant confuses the
  // compiler)

  virtual std::vector<DataFieldReference> _getDataFieldReferences() = 0;

  friend eipScanner::utils::Buffer &
  operator<<(eipScanner::utils::Buffer &outStream,
             BaseAssemblyData &assemblyData);

  friend eipScanner::utils::Buffer &
  operator>>(eipScanner::utils::Buffer &inStream,
             BaseAssemblyData &assemblyData);
};
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_BASEASSEMBLYDATA_H
