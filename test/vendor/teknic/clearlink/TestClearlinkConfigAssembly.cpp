//
// Created by Jan Ritzenhoff on 12/5/24.
//

#include <gmock/gmock-more-actions.h>
#include <gmock/gmock-spec-builders.h>
#include <gtest/gtest.h>

#include "EIPScanner/cip/MessageRouterResponse.h"
#include "EIPScanner/vendor/teknic/clearlink/ConfigAssemblyObject.h"
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
                                         const std::vector<uint8_t> &data) -> eipScanner::cip::MessageRouterResponse {
        calledDataSize = data.size();

        // just need to make the lambda happy
        return eipScanner::cip::MessageRouterResponse();
      }));

  ConfigAssemblyObject inputAssemblyObject(_nullSession, _messageRouter);
  inputAssemblyObject.setAssembly();

  EXPECT_EQ(232, calledDataSize);
}