//
// Created by Jan Ritzenhoff on 12/04/24.
//
#include <gtest/gtest.h>

#include "EIPScanner/cip/Types.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/IOInputData.h"

using namespace eipScanner::vendor::teknic::clearlink::assembly::input;

class TestIOInputDataRig : public ::testing::Test, public IOInputData {
public:
  void SetUp() override { }
};

class TestIOInputData : public IOInputData
{
public:
  void publicSetDipValue(const std::vector<eipScanner::cip::CipBool> dipValue) {
    setDipValue(dipValue);
  }
  void publicSetDipStatus(const std::vector<eipScanner::cip::CipBool> dipStatus) {
    setDipStatus(dipStatus);
  }
  void publicSetAipValue(const std::vector<eipScanner::cip::CipUint> aipValue) {
    setAipValue(aipValue);
  }
};


TEST_F(TestIOInputDataRig, CreateIOInputDataBuffer) {

  TestIOInputData ioInputData;

  // Initialize the IOInputData object
  ioInputData.publicSetDipValue({0x6, 0x2});
  ioInputData.publicSetDipStatus({0x2});
  ioInputData.publicSetAipValue({0x0, 0x9});

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

TEST_F(TestIOInputDataRig, ReadIOInputDataBuffer) {
  IOInputData ioInputData;

  std::vector<eipScanner::cip::CipBool> dipValue = {0b00000010, 0b00001000};
  std::vector<eipScanner::cip::CipBool> dipStatus = {0b00001000, 0x0};
  std::vector<eipScanner::cip::CipUint> aipValue = {0x3, 0x0, 0x0, 0x0};

  eipScanner::utils::Buffer startingBuffer;
  startingBuffer << dipValue << dipStatus << aipValue;

  startingBuffer >> ioInputData;

  EXPECT_TRUE(ioInputData.getDigitalInputValue(IOInputData::DigitalInput::AI_11));
  EXPECT_FALSE( ioInputData.getDigitalInputStatus(IOInputData::DigitalInput::IO_2));
  EXPECT_TRUE( ioInputData.getDigitalInputStatus(IOInputData::DigitalInput::IO_3));
  EXPECT_EQ(0x3, ioInputData.getAnalogInputValue(IOInputData::AnalogInput::AI_9));
}