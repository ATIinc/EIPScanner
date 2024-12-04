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

    // Initialize the IOInputData object
    _ioInputData.setDipValue({ 0x1, 0x2, 0x3, 0x4 });
    _ioInputData.setDipStatus(0x2);
    _ioInputData.setAipValue(0x9);

    // Write the data to a buffer
    eipScanner::utils::Buffer actualBuffer;
    actualBuffer << _ioInputData;

    // Compare the actual buffer to the expected
    std::vector<eipScanner::cip::CipBool> dipValue = { 0x1, 0x2, 0x3, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
    eipScanner::cip::CipDint dipStatus = 0x2;
    eipScanner::cip::CipDint aipValue = 0x9;

    eipScanner::utils::Buffer expectedBuffer;
    expectedBuffer << dipValue << dipStatus << aipValue;

    EXPECT_EQ(expectedBuffer.data(), actualBuffer.data());
}

TEST_F(TestIOInputData, ShouldReadBuffer) {

    std::vector<eipScanner::cip::CipBool> dipValue = { 0x2, 0x8, 0x1, 0x2, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
    eipScanner::cip::CipDint dipStatus = 0x8;
    eipScanner::cip::CipDint aipValue = 0x3;

    eipScanner::utils::Buffer startingBuffer;
    startingBuffer << dipValue << dipStatus << aipValue;


    startingBuffer >> _ioInputData; 

    EXPECT_EQ(dipValue, _ioInputData.getDipValue());
    EXPECT_EQ(dipStatus, _ioInputData.getDipStatus());
    EXPECT_EQ(aipValue, _ioInputData.getAipValue());
}