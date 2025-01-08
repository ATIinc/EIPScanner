//
// Created by Jan Ritzenhoff on 12/4/2024
//

// Based on:
//	Assembly Object - IO Input Data (04hex - 1 instance)
//		*
// https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18

#ifndef EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_IOINPUTDATA_H
#define EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_IOINPUTDATA_H

#include "EIPScanner/cip/Types.h"

#include "EIPScanner/vendor/teknic/clearlink/assembly/BaseAssemblyData.h"
#include <iterator>

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace assembly {
namespace input {
/**
 * @class IOInputData
 *
 * @brief Implements the Step & Direction IO Input Data section
 */
class IOInputData : public BaseAssemblyData {
public:
  /**
   * @brief Creates an instance that reads a buffer
   * @param data
   */
  IOInputData();

  // -------------------------------------------------------------

  enum class DigitalInput : uint8_t {
    IO_0 = 0,
    IO_1 = 1,
    IO_2 = 2,
    IO_3 = 3,
    IO_4 = 4,
    IO_5 = 5,
    DI_6 = 6,
    DI_7 = 7,
    DI_8 = 8,
    AI_9 = 9,
    AI_10 = 10,
    AI_11 = 11,
    AI_12 = 12,
  };

  enum class DigitalOutput : uint8_t {
    IO_0 = 0,
    IO_1 = 1,
    IO_2 = 2,
    IO_3 = 3,
    IO_4 = 4,
    IO_5 = 5,
  };

  enum class AnalogInput : uint8_t {
    AI_9 = 0,
    AI_10 = 1,
    AI_11 = 2,
    AI_12 = 3,
  };

  enum class AnalogOutput : uint8_t {
    IO_0 = 4,
  };

  const eipScanner::cip::CipBool
  getDigitalInputValue(DigitalInput digitalInput);
  const eipScanner::cip::CipBool
  getDigitalInputStatus(DigitalInput digitalInput);
  const eipScanner::cip::CipInt getAnalogInputValue(AnalogInput analogInput);
  const eipScanner::cip::CipBool getAnalogInputStatus(AnalogInput analogInput);
  const eipScanner::cip::CipBool
  getAnalogOutputStatus(AnalogOutput analogOutput);

protected:
  void setDipValue(const std::vector<eipScanner::cip::CipBool> dipValue);
  void setDipStatus(const std::vector<eipScanner::cip::CipBool> dipStatus);
  void setAipValue(const std::vector<eipScanner::cip::CipUint> aipValue);

private:
  std::vector<DataFieldReference> _getDataFieldReferences() override;

  template <typename T>
  bool _getBitValueFromVector(const typename std::vector<T> &vec,
                              size_t bitIndex) {
    size_t typeByteSize = sizeof(T);
    size_t typeBitSize = typeByteSize * BITS_IN_A_BYTE;

    size_t arrayElement = bitIndex / typeBitSize;
    size_t indexInsideElement = bitIndex % typeBitSize;

    return vec.at(arrayElement) & (1 << indexInsideElement);
  }

  // CONSTANTS
  static const size_t BITS_IN_A_BYTE = 8;
  static const size_t DIP_VALUE_SIZE = 2;  // 13 bits
  static const size_t DIP_STATUS_SIZE = 2; // 13 bits
  static const size_t AIP_VALUE_SIZE = 4;
  static const size_t AIOP_STATUS_SIZE = 2; // 5 bits
  static const size_t DOP_STATUS_SIZE = 2;  // 6 bits
  static const size_t PADDING_BYTES_SIZE = 3;

  // Actual field members

  // Digital Input Value == The state of the Clearlink Input Connector Pin
  std::vector<eipScanner::cip::CipBool> _dipValue;

  // Digital Input Status == Will return true (if the assocaited input has been
  // configured as an analog IO)
  std::vector<eipScanner::cip::CipBool> _dipStatus;
  // NOTE: Cheating a little bit because no signed-int16 buffering exists
  std::vector<eipScanner::cip::CipUint> _aipValue;
  std::vector<eipScanner::cip::CipBool> _aiopStatus;
  std::vector<eipScanner::cip::CipBool> _dopStatus;
  eipScanner::cip::CipUlint _ccioInputValue;
  eipScanner::cip::CipUlint _ccioStatus;
  eipScanner::cip::CipUsint _ccioBoardCount;
  std::vector<eipScanner::cip::CipByte> _reservedPadding;
};

} // namespace input
} // namespace assembly
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner

#endif // EIPSCANNER_VENDOR_TEKNIC_CLEARLINK_ASSEMBLY_INPUT_IOINPUTDATA_H
