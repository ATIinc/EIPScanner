//
// Created by Jan Ritzenhoff on 12/5/24.
//

#include <cstdint>
#include <gmock/gmock-more-actions.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include "EIPScanner/MessageRouter.h"
#include "EIPScanner/cip/GeneralStatusCodes.h"
#include "EIPScanner/cip/MessageRouterResponse.h"
#include "EIPScanner/vendor/teknic/clearlink/ConfigAssemblyObject.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/MotorConfigData.h"
#include "Mocks.h"

using ::testing::_;
using ::testing::Invoke;

using namespace eipScanner;
using namespace eipScanner::vendor::teknic::clearlink;

class TestMotorConfigAssembly : public ::testing::Test {
public:
  void SetUp() override {
    _messageRouter = std::make_shared<TMockMessageRouter>();
    _nullSession = nullptr;
  }

  TMockMessageRouter::SPtr _messageRouter;
  SessionInfoIf::SPtr _nullSession;
};

TEST_F(TestMotorConfigAssembly, ShouldSendAllMessageBytes) {

  size_t calledDataSize = 0;

  EXPECT_CALL(*_messageRouter, sendRequest(_, _, _, _))
      .WillOnce(Invoke([&calledDataSize](eipScanner::SessionInfoIf::SPtr si,
                                         eipScanner::cip::CipUsint service,
                                         const eipScanner::cip::EPath &path,
                                         const std::vector<uint8_t> &data)
                           -> eipScanner::cip::MessageRouterResponse {
        calledDataSize = data.size();

        // just need to make the lambda happy
        return eipScanner::cip::MessageRouterResponse();
      }));

  ConfigAssemblyObject inputAssemblyObject(_nullSession, _messageRouter);
  inputAssemblyObject.setAssembly();

  EXPECT_EQ(232, calledDataSize);
}

TEST_F(TestMotorConfigAssembly, SendingCorrectBytes) {

  std::vector<uint8_t> actualBufferData = {};

  EXPECT_CALL(*_messageRouter, sendRequest(_, _, _, _))
      .WillOnce(Invoke([&actualBufferData](eipScanner::SessionInfoIf::SPtr si,
                                           eipScanner::cip::CipUsint service,
                                           const eipScanner::cip::EPath &path,
                                           const std::vector<uint8_t> &data)
                           -> eipScanner::cip::MessageRouterResponse {
        actualBufferData = data;
        return eipScanner::cip::MessageRouterResponse();
      }));

  ConfigAssemblyObject inputAssemblyObject(_nullSession, _messageRouter);

  assembly::config::MotorConfigData motorConfigData =
      inputAssemblyObject.getMotor0ConfigData();
  motorConfigData.setHomeSensorConnector(5);
  motorConfigData.setBrakeOutputConnector(6);
  motorConfigData.setStopSensorConnector(7);
  inputAssemblyObject.setMotor0ConfigData(motorConfigData);

  inputAssemblyObject.setAssembly();

  std::vector<uint8_t> expectedBufferData(232, 0x0);
  expectedBufferData[106] = 5;
  expectedBufferData[107] = 6;
  expectedBufferData[108] = 2;

  EXPECT_EQ(expectedBufferData.size(), actualBufferData.size());
  EXPECT_EQ(::testing::PrintToString(expectedBufferData),
            ::testing::PrintToString(actualBufferData));
}

TEST_F(TestMotorConfigAssembly, ReadingCorrectBytes) {

  std::vector<uint8_t> fakedBufferResponseData(232, 0x0);
  fakedBufferResponseData[106] = 10;
  fakedBufferResponseData[107] = 8;
  fakedBufferResponseData[108] = 7;

   EXPECT_CALL(*_messageRouter, sendRequest(_, _, _, _))
      .WillOnce(Invoke([&fakedBufferResponseData](eipScanner::SessionInfoIf::SPtr si,
                                           eipScanner::cip::CipUsint service,
                                           const eipScanner::cip::EPath &path,
                                           const std::vector<uint8_t> &data)
                           -> eipScanner::cip::MessageRouterResponse {
        
        eipScanner::cip::MessageRouterResponse response = eipScanner::cip::MessageRouterResponse();
        response.setData(fakedBufferResponseData);
        return response;
      }));

  ConfigAssemblyObject inputAssemblyObject(_nullSession, _messageRouter);
  inputAssemblyObject.getAssembly();

  assembly::config::MotorConfigData motorConfigData =
      inputAssemblyObject.getMotor0ConfigData();

  EXPECT_EQ(10, motorConfigData.getHomeSensorConnector());
  EXPECT_EQ(8, motorConfigData.getBrakeOutputConnector());
  EXPECT_EQ(7, motorConfigData.getStopSensorConnector());
}