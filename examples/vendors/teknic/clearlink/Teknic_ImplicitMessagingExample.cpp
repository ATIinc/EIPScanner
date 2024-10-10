//
// Created by Jan Ritzenhoff on 10/09/24.
//

#include <sstream>

#include <EIPScanner/cip/connectionManager/NetworkConnectionParams.h>
#include <EIPScanner/SessionInfo.h>
#include <EIPScanner/ConnectionManager.h>
#include <EIPScanner/utils/Logger.h>
#include <EIPScanner/utils/Buffer.h>

using namespace eipScanner::cip;
using eipScanner::ConnectionManager;
using eipScanner::MessageRouter;
using eipScanner::SessionInfo;
using eipScanner::cip::connectionManager::ConnectionParameters;
using eipScanner::cip::connectionManager::NetworkConnectionParams;
using eipScanner::utils::Buffer;
using eipScanner::utils::Logger;
using eipScanner::utils::LogLevel;

// $       0 = 1  (O=>T fixed)
// $       1 = 0  (O=>T variable)
// $       2 = 1  (T=>O fixed)
// $       3 = 0  (T=>O variable)
// $     4-7 = 0  (reserved (must be zero))
// $    8-10 = 4  (O=>T header (4 byte run/idle))
// $      11 = 0  (reserved (must be zero))
// $   12-14 = 0  (T=>O header (pure data))
// $      15 = 0  (reserved (must be zero))
// $      16 = 0  (O=>T connection type: NULL)
// $      17 = 0  (O=>T connection type: MULTI)
// $      18 = 1  (O=>T connection type: P2P)
// $      19 = 0  (O=>T connection type: RSVD)
// $      20 = 0  (T=>O connection type: NULL)
// $      21 = 1  (T=>O connection type: MULTI)
// $      22 = 0  (T=>O connection type: P2P)
// $      23 = 0  (T=>O connection type: RSVD)
// $      24 = 0  (O=>T priority: LOW)
// $      25 = 0  (O=>T priority: HIGH)
// $      26 = 1  (O=>T priority: SCHEDULED)
// $      27 = 0  (O=>T priority: RSVD)
// $      28 = 0  (T=>O priority: LOW)
// $      29 = 0  (T=>O priority: HIGH)
// $      30 = 1  (T=>O priority: SCHEDULED)
// $      31 = 0  (T=>O priority: RSVD)
enum ClearlinkNetworkConnectionParams : CipUdint {
  O2T_FIXED = 0,
  T2O_FIXED = (1 << 2),

  O2T_HEADER = (4 << 8),

  O2T_P2P_CONNECTION = (1 << 18),
  T2O_MULTI_CONNECTION = (1 << 21),

  O2T_SCHEDULED_PRIORITY = (1 << 26),
  T2O_SCHEDULED_PRIORITY = (1 << 30),
};

void dataListenerCallback(eipScanner::cip::CipUdint realTimeHeader, eipScanner::cip::CipUint sequence, const std::vector<uint8_t>& data)
{
  std::ostringstream ss;
  ss << "secNum=" << sequence << " data=";
  for (auto &byte : data) {
    ss << "[" << std::hex << (int) byte << "]";
  }

  Logger(LogLevel::INFO) << "Received: " << ss.str(); 
}

void closeListenerCallback()
{ 
  Logger(LogLevel::INFO) << "Closed"; 
}


int main()
{
  Logger::setLogLevel(LogLevel::DEBUG);

  auto sessionInfo = std::make_shared<SessionInfo>("192.168.1.109", 0xAF12);

  /* Implicit messaging notes: (* https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=11)
    - Input Assembly is feedback information FROM Clearlink TO the Scanner
    - Output Assembly is command instructions FROM Scanner TO the Clearlink
    - Configuration Assembly contains ClearLink setup data that does not typically change during runtime

    - The Originator is the Scanner
    - The Target is the Clearlink
  */

  /* From the EDS file:
    - There are 4 different Connection Options in the Connection Manager. 
      * We want the 'Connection1' option as it has the "connection name" == 'Step & Dir'
      * The `Connection1` object has an associated "exclusive-owner-path" which is saved here as the 'connectionPath'
    
    - The O2T (Originator => Target) assembly is defined under 'Connection1'
      * 'Param999,280,Assem112,  $ O=>T RPI, size in bytes, format'
        * 'Param999'  : refers to a Parameter defined in the '[Params]' section of the EDS file
        * '280'       : size of the Assembly in bytes
        * 'Assem112'  : refers to the Assembly defined in the '[Assembly]' section of the EDS file
      
      * NOTE: The ClearLink object reference has a more user-friendly breakdown of the Assembly (instance 112) -- Step & Dir Output Assembly
        * https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=19
        * 
    - The T20 (Target => Originator) assembly is defined under 'Connection1'
      * NOTE: The ClearLink object reference has a more user-friendly breakdown of the Assembly (instance 100) -- Step & Dir Input Assembly
        * https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=19   

  */

  ConnectionManager connectionManager;

  ConnectionParameters parameters;
  parameters.o2tRealTimeFormat = true;

  parameters.originatorVendorId = 342;        // Vendor ID of the Scanner (using default)
  parameters.originatorSerialNumber = 32423;  // Serial # of the Scanner (using default)

  parameters.o2tNetworkConnectionParams |= NetworkConnectionParams::P2P; 
  parameters.o2tNetworkConnectionParams |= NetworkConnectionParams::SCHEDULED_PRIORITY;
  parameters.o2tNetworkConnectionParams |= 280; // size of Assm112 = 280 (Step & Direction Output Assembly)

  parameters.t2oNetworkConnectionParams |= NetworkConnectionParams::P2P;
  parameters.t2oNetworkConnectionParams |= NetworkConnectionParams::SCHEDULED_PRIORITY;
  parameters.t2oNetworkConnectionParams |= 332; // size of Assm100 = 332 (Step & DIrection Input Assembly)

  //  0x20 0x04 CONFIG_ASSEMBLY_ID 0x2C OUTPUT_ASSEMBLY_ID 0x2C INPUT_ASSEMBLY
  parameters.connectionPath = {0x20, 0x04, 0x24, 0x96, 0x2C, 0x70, 0x2C, 0x64}; // exclusive owner path (includes Assm112 and Assem100)

  parameters.originatorSerialNumber = 0x12345;
  parameters.o2tRPI = 10000;                // saved as Param999 which has the following line: '1000,1000000,10000,     $ min, max, default data values' 
  parameters.t2oRPI = 10000;

  // Class 1 is Implicit Messaging and Class 3 is Explicit Messaging
  parameters.transportTypeTrigger |= NetworkConnectionParams::CLASS1;

  eipScanner::IOConnection::WPtr io = connectionManager.forwardOpen(sessionInfo, parameters);
  if (auto ptr = io.lock())
  {
    ptr->setDataToSend(std::vector<uint8_t>(280));

    ptr->setReceiveDataListener(dataListenerCallback);

    ptr->setCloseListener(closeListenerCallback);
  }

  int count = 200;
  while (connectionManager.hasOpenConnections() && count-- > 0)
  {
    connectionManager.handleConnections(std::chrono::milliseconds(100));
  }

  connectionManager.forwardClose(sessionInfo, io);

  return EXIT_SUCCESS;
}
