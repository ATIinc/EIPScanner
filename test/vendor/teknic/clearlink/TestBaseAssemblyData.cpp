//
// Created by Jan Ritzenhoff on 12/04/24.
//


#include <gtest/gtest.h>
#include "Mocks.h"      // contains the TMockMessageRouter class
#include "EIPScanner/vendor/teknic/clearlink/utils/BaseAssemblyData.h"

using namespace eipScanner;
using namespace eipScanner::vendor::teknic::clearlink::utils;

class TestBaseAssemblyData : public ::testing::Test {
public:
	void SetUp() override {
		_ioInputData = BaseAssemblyData();
	}

    BaseAssemblyData _ioInputData;
};

TEST_F(TestBaseAssemblyData, ShouldCreateBuffer) {

    // _ioInputData.dipValue = { 0x1, 0x2, 0x3, 0x4 };

    eipScanner::utils::Buffer buffer;
    buffer << _ioInputData;

    
    eipScanner::utils::Buffer expectedBuffer;
    expectedBuffer << 0x1 << 0x2 << 0x3 << 0x4;

    EXPECT_EQ(expectedBuffer.data(), buffer.data());
}