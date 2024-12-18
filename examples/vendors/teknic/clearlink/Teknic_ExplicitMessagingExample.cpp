//
// Created by Aleksey Timin on 11/16/19.
//

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64)
#include <winsock2.h>
#define OS_Windows (1)
#endif

#include <EIPScanner/ConnectionManager.h>
#include <EIPScanner/MessageRouter.h>
#include <EIPScanner/SessionInfo.h>
#include <EIPScanner/cip/connectionManager/NetworkConnectionParams.h>
#include <EIPScanner/utils/Buffer.h>
#include <EIPScanner/utils/Logger.h>
#include <cstdlib>
#include <sstream>

using namespace eipScanner::cip;
using eipScanner::ConnectionManager;
using eipScanner::MessageRouter;
using eipScanner::SessionInfo;
using eipScanner::cip::connectionManager::ConnectionParameters;
using eipScanner::cip::connectionManager::NetworkConnectionParams;
using eipScanner::utils::Buffer;
using eipScanner::utils::Logger;
using eipScanner::utils::LogLevel;

int main() {
  Logger::setLogLevel(LogLevel::DEBUG);

  auto si = std::make_shared<SessionInfo>("192.168.1.71", 0xAF12,
                                          std::chrono::seconds(10));
  auto messageRouter = std::make_shared<MessageRouter>(true);

  // Read attribute
  auto readResponse =
      messageRouter->sendRequest(si, ServiceCodes::GET_ATTRIBUTE_SINGLE,
                                 eipScanner::cip::EPath(0x04, 0x96, 0x3), {});

  if (readResponse.getGeneralStatusCode() != GeneralStatusCodes::SUCCESS) {
    Logger(LogLevel::ERROR) << "We got READ error=0x" << std::hex
                            << readResponse.getGeneralStatusCode();
  }

  auto logger = Logger(LogLevel::INFO);

  logger << "Read data value (" << readResponse.getData().size() << "): ";
  for (auto byte : readResponse.getData()) {

    logger << (int)byte << ",";
  }
  logger << "\n";

  std::vector<uint8_t> validConfiguration = {
      0x64, 0x64, 0x64, 0x64, 0x64, 0x00, 0x00, 0x00,

      0x0a, 0x0a, 0x0a, 0x0a,
      0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27,
      0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27,
      0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27,
      0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27, 0x10, 0x27,
      0x10, 0x27, 0x10, 0x27,
      0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a,
      
      0x64, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
      0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x96, 0x98, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
      0x01, 0x00, 0x00, 0x00, 0x80, 0x96, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00,
      0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
      0x80, 0x96, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x08, 0x00, 0x00, 0x00,
      0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x80, 0x96, 0x98, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
      0xff, 0xff, 0xff, 0x00, 0x00, 0xc2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
      0x0a, 0x00, 0x00, 0x00};

  auto writeResponse = messageRouter->sendRequest(
      si, ServiceCodes::SET_ATTRIBUTE_SINGLE,
      eipScanner::cip::EPath(0x04, 0x96, 0x3), validConfiguration);

  if (writeResponse.getGeneralStatusCode() != GeneralStatusCodes::SUCCESS) {
    Logger(LogLevel::ERROR) << "We got WRITE error=0x" << std::hex
                            << writeResponse.getGeneralStatusCode();
  }

  return EXIT_SUCCESS;
}
