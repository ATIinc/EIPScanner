//
// Created by Jan Ritzenhoff on 12/04/24.
//
#include <gtest/gtest.h>

#include "EIPScanner/vendor/teknic/clearlink/assembly/input/SerialAsciiInputData.h"

using namespace eipScanner::vendor::teknic::clearlink::assembly::input;

class TestSerialAsciiInputData : public ::testing::Test {
public:
  void SetUp() override {}
};

TEST_F(TestSerialAsciiInputData, CreateSerialAsciiInputDataBuffer) {
  SerialAsciiInputData serialAsciiInputData;

  eipScanner::utils::Buffer actualBuffer;
  actualBuffer << serialAsciiInputData;

  // Bytes 180 through 331
  EXPECT_EQ(152, actualBuffer.size());
}