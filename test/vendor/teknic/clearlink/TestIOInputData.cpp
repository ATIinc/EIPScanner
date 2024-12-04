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

    _ioInputData.setDipValue({ 0x1, 0x2, 0x3, 0x4 });
    _ioInputData.setDipStatus(0x2);
    _ioInputData.setAipValue(0x9);

    eipScanner::utils::Buffer buffer;
    buffer << _ioInputData;

    
    eipScanner::utils::Buffer expectedBuffer;

    std::vector<eipScanner::cip::CipBool> dipValue = { 0x1, 0x2, 0x3, 0x4 };
    eipScanner::cip::CipDint dipStatus = 0x2;
    eipScanner::cip::CipDint aipValue = 0x9;

    // dip value is size 13
    expectedBuffer << dipValue << dipStatus << aipValue;

    EXPECT_EQ(expectedBuffer.data(), buffer.data());
}