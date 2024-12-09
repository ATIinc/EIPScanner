//
// Created by Jan Ritzenhoff on 12/9/24.
//

#include <EIPScanner/cip/EPath.h>

#include <EIPScanner/IdentityObject.h>
#include <EIPScanner/utils/Logger.h>
#include <EIPScanner/MessageRouter.h>

#include <EIPScanner/vendor/teknic/clearlink/SDMotorConfigObject.h>

using eipScanner::IdentityObject;
using eipScanner::SessionInfo;
using eipScanner::MessageRouter;
using eipScanner::cip::ServiceCodes;
using eipScanner::cip::EPath;
using eipScanner::utils::Logger;
using eipScanner::utils::LogLevel;

int main() {
  Logger::setLogLevel(LogLevel::DEBUG);

  auto si = std::make_shared<SessionInfo>("192.168.1.71", 0xAF12);
  auto messageRouter = std::make_shared<MessageRouter>(true);

  auto configObject = eipScanner::vendor::teknic::clearlink::SDMotorConfigObject(3, si, messageRouter);

  // Read attribute

  Logger(LogLevel::INFO) << (int) configObject.getConfigRegister() << "\n"
    << (int) configObject.getSoftLimitPosition1() << "\n"
    << (int) configObject.getSoftLimitPosition2() << "\n"
    << (int) configObject.getPositiveLimitConnector() << "\n"
    << (int) configObject.getNegativeLimitConnector() << "\n"
    << (int) configObject.getHomeSensorConnector() << "\n"
    << (int) configObject.getBrakeOutputConnector() << "\n"
    << (int) configObject.getTriggerPositionCaptureConnector() << "\n"
    << (int) configObject.getMaxDecelerationRate() << "\n"
    << (int) configObject.getStopSensorConnector() << "\n"
    << (int) configObject.getFollowEncoderMode() << "\n"
    << (int) configObject.getFollowDivisor() << "\n"
    << (int) configObject.getFollowMultiplier() << "\n";

  return EXIT_SUCCESS;
}
