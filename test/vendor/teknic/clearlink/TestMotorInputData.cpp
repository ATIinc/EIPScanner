//
// Created by Jan Ritzenhoff on 12/04/24.
//
#include <gtest/gtest.h>

#include "EIPScanner/vendor/teknic/clearlink/assembly/input/MotorInputData.h"

using namespace eipScanner::vendor::teknic::clearlink::assembly::input;

class TestMotorInputData : public ::testing::Test {
public:
  void SetUp() override {}
};

TEST_F(TestMotorInputData, CreateMotorInputDataBuffer) {
  MotorInputData motorInputData;

  eipScanner::utils::Buffer actualBuffer;
  actualBuffer << motorInputData;

  // Bytes 52 through 83
  EXPECT_EQ(32, actualBuffer.size());
}