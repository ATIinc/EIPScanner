//
// Created by Jan Ritzenhoff on 12/04/24.
//

#include "EIPScanner/cip/Types.h"
#include "EIPScanner/vendor/teknic/clearlink/utils/IOInputData.h"
#include "Mocks.h" // contains the TMockMessageRouter class
#include <gtest/gtest.h>

using namespace eipScanner;
using namespace eipScanner::vendor::teknic::clearlink::utils;

class TestIOInputData : public ::testing::Test {
public:
  void SetUp() override { _ioInputData = IOInputData(); }

  IOInputData _ioInputData;
};

TEST_F(TestIOInputData, ShouldCreateBuffer) {

  // Initialize the IOInputData object
  _ioInputData.setDipValue({0x6, 0x2});
  _ioInputData.setDipStatus({0x2});
  _ioInputData.setAipValue({0x0, 0x9});

  // Write the data to a buffer
  eipScanner::utils::Buffer actualBuffer;
  actualBuffer << _ioInputData;

  // Compare the actual buffer to the expected
  std::vector<eipScanner::cip::CipBool> dipValue = {0x6, 0x2};
  std::vector<eipScanner::cip::CipBool> dipStatus = {0x2, 0x0};
  std::vector<eipScanner::cip::CipUint> aipValue = {0x0, 0x9, 0x0, 0x0};

  // Should be a total of 36 bytes (according to https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18)
  std::vector<eipScanner::cip::CipByte> remainingDataPadding(23);

  eipScanner::utils::Buffer expectedBuffer;
  expectedBuffer << dipValue << dipStatus << aipValue << remainingDataPadding;

  EXPECT_EQ(expectedBuffer.size(), actualBuffer.size());
  EXPECT_EQ(expectedBuffer.data(), actualBuffer.data());
}

TEST_F(TestIOInputData, ShouldReadBuffer) {

  std::vector<eipScanner::cip::CipBool> dipValue = {0x2, 0x8};
  std::vector<eipScanner::cip::CipBool> dipStatus = {0x8, 0x0};
  std::vector<eipScanner::cip::CipUint> aipValue = {0x3, 0x0, 0x0, 0x0};

  eipScanner::utils::Buffer startingBuffer;
  startingBuffer << dipValue << dipStatus << aipValue;

  startingBuffer >> _ioInputData;

  EXPECT_EQ(dipValue, _ioInputData.getDipValue());
  EXPECT_EQ(dipStatus, _ioInputData.getDipStatus());
  EXPECT_EQ(aipValue, _ioInputData.getAipValue());
}