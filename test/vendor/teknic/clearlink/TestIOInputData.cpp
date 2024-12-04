//
// Created by Jan Ritzenhoff on 12/04/24.
//


#include <gtest/gtest.h>
#include "Mocks.h"      // contains the TMockMessageRouter class
#include "EIPScanner/vendor/teknic/clearlink/utils/IOInputData.h"

using namespace eipScanner;
using namespace eipScanner::vendor::teknic::clearlink::utils;

class TestIOInputData : public ::testing::Test {
public:
	void SetUp() override {
		_ioInputData = IOInputData();
	}

    IOInputData _ioInputData;
};

TEST_F(TestIOInputData, ShouldCreateBuffer) {

    _ioInputData.dipValue = { 0x1, 0x2, 0x3, 0x4 };

    std::vector<uint8_t> buffer;
    buffer << _ioInputData;

    
    std::vector<uint8_t> expectedBuffer = { 0x1, 0x2, 0x3, 0x4 };

    EXPECT_EQ(expectedBuffer, buffer);
}