//
// Created by Jan Ritzenhoff on 12/04/24.
//
#include <gtest/gtest.h>

#include "EIPScanner/cip/Types.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/IOInputData.h"

using namespace eipScanner::vendor::teknic::clearlink::assembly::input;

class TestIOInputData : public ::testing::Test, public IOInputData {
public:
  void SetUp() override { }
};

TEST_F(TestIOInputData, CreateIOInputDataBuffer) {

  IOInputData ioInputData;

  // Initialize the IOInputData object
  ioInputData.setDipValue({0x6, 0x2});
  ioInputData.setDipStatus({0x2});
  ioInputData.setAipValue({0x0, 0x9});

  // Write the data to a buffer
  eipScanner::utils::Buffer actualBuffer;
  actualBuffer << ioInputData;

  // Compare the actual buffer to the expected
  std::vector<eipScanner::cip::CipBool> dipValue = {0x6, 0x2};
  std::vector<eipScanner::cip::CipBool> dipStatus = {0x2, 0x0};
  std::vector<eipScanner::cip::CipUint> aipValue = {0x0, 0x9, 0x0, 0x0};

  // Should be a total of 36 bytes (according to https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=18)
  std::vector<eipScanner::cip::CipByte> remainingDataPadding(24);

  eipScanner::utils::Buffer expectedBuffer;
  expectedBuffer << dipValue << dipStatus << aipValue << remainingDataPadding;

  EXPECT_EQ(expectedBuffer.size(), actualBuffer.size());
  EXPECT_EQ(expectedBuffer.data(), actualBuffer.data());
}

TEST_F(TestIOInputData, ReadIOInputDataBuffer) {
  IOInputData ioInputData;

  std::vector<eipScanner::cip::CipBool> dipValue = {0x2, 0x8};
  std::vector<eipScanner::cip::CipBool> dipStatus = {0x8, 0x0};
  std::vector<eipScanner::cip::CipUint> aipValue = {0x3, 0x0, 0x0, 0x0};

  eipScanner::utils::Buffer startingBuffer;
  startingBuffer << dipValue << dipStatus << aipValue;

  startingBuffer >> ioInputData;

  EXPECT_EQ(dipValue, ioInputData.getDipValue());
  EXPECT_EQ(dipStatus, ioInputData.getDipStatus());
  EXPECT_EQ(aipValue, ioInputData.getAipValue());
}