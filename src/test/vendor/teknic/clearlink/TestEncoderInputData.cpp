//
// Created by Jan Ritzenhoff on 12/04/24.
//
#include <gtest/gtest.h>

#include "EIPScanner/cip/Types.h"
#include "EIPScanner/vendor/teknic/clearlink/utils/EncoderInputData.h"

namespace eipScanner {
namespace vendor {
namespace teknic {
namespace clearlink {
namespace utils {

class TestEncoderInputData : public ::testing::Test {
public:
  void SetUp() override { }
};

TEST_F(TestEncoderInputData, CreateEncoderInputDataBuffer) {
  EncoderInputData encoderInputData;

  eipScanner::utils::Buffer actualBuffer;
  actualBuffer << encoderInputData;

  // Bytes 26 through 51
  EXPECT_EQ(15, actualBuffer.size());

}

TEST_F(TestEncoderInputData, ReadEncoderInputDataBuffer) {
  std::vector<eipScanner::cip::CipBool> dipValue = {0x2, 0x8};
  std::vector<eipScanner::cip::CipBool> dipStatus = {0x8, 0x0};
  std::vector<eipScanner::cip::CipUint> aipValue = {0x3, 0x0, 0x0, 0x0};

  eipScanner::utils::Buffer startingBuffer;
  startingBuffer << dipValue << dipStatus << aipValue;

  EncoderInputData encoderInputData;
  startingBuffer >> encoderInputData;

  EXPECT_EQ(10, encoderInputData._encoderPosition);

}

} // namespace utils
} // namespace clearlink
} // namespace teknic
} // namespace vendor
} // namespace eipScanner