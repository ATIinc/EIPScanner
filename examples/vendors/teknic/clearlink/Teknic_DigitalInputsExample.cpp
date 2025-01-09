#include <cstdint>
#include <memory>

#include <EIPScanner/cip/Types.h>
#include <EIPScanner/utils/Logger.h>
#include <EIPScanner/vendor/teknic/clearlink/ConfigAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/InputAssemblyObject.h>
#include <EIPScanner/vendor/teknic/clearlink/OutputAssemblyObject.h>
#include "EIPScanner/vendor/teknic/clearlink/assembly/config/IOModeConfigData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/input/IOInputData.h"
#include "EIPScanner/vendor/teknic/clearlink/assembly/output/IOOutputData.h"

using namespace eipScanner::vendor::teknic;
using eipScanner::vendor::teknic::clearlink::assembly::config::IOModeConfigData;
using eipScanner::vendor::teknic::clearlink::assembly::input::IOInputData;
using eipScanner::vendor::teknic::clearlink::assembly::output::IOOutputData;

struct ClearlinkIO {
  clearlink::ConfigAssemblyObject config;
  clearlink::InputAssemblyObject input;
  clearlink::OutputAssemblyObject output;
};


clearlink::assembly::input::IOInputData getClearlinkInputs(clearlink::InputAssemblyObject clearlinkInput)
{
	return clearlinkInput.getIOInputData();
}

void setClearlinkOutputs(clearlink::InputAssemblyObject &clearlinkInput,
                    			clearlink::assembly::input::IOInputData  ioInputData)
{
	clearlinkInput.setIOInputData(ioInputData);
}

// ------------------------------
// initialize the object assembly wrappers
// -------------
ClearlinkIO createClearlinkIOObjects(std::string ipAddress, int port)
{
	// EthernetIP variables
	const auto sessionInfoPtr = std::make_shared<eipScanner::SessionInfo>(ipAddress, port);

	// need to make sure that the EPath is padded in 8-bit segments or the MessageRouter SET_ATTRIBUTE_SINGLE request will fail
	const auto messageRouterPtr = std::make_shared<eipScanner::MessageRouter>(true);

	auto clearlinkConfiguration = clearlink::ConfigAssemblyObject(sessionInfoPtr, messageRouterPtr);
	auto clearlinkInput = clearlink::InputAssemblyObject(sessionInfoPtr, messageRouterPtr);
	auto clearlinkOutput = clearlink::OutputAssemblyObject(sessionInfoPtr, messageRouterPtr);

	return {clearlinkConfiguration, clearlinkInput, clearlinkOutput};
}

int main(int argc, char *argv[]) {

  uint8_t inputIndex = 0;
	uint8_t onValue = 0;

  if (argc > 1) {
    inputIndex = std::stoi(argv[1]);
  }

  eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
      << "Reading input " << std::to_string(inputIndex) << std::flush;

  // Get the clearlinkIO (given a variable IP address and the default
  // Ethernet/IP port)
  ClearlinkIO clearlinkRepresentation =
      createClearlinkIOObjects("172.31.19.10", 0xAF12);

	// Make sure the config is written
	clearlinkRepresentation.config.setAssembly();


	// Initialize the output values
	clearlinkRepresentation.input.getAssembly();

	// Convert to digital output
	IOInputData::DigitalInput requestedInput = static_cast<IOInputData::DigitalInput>(inputIndex);

	// Set the IO output data
	clearlink::assembly::input::IOInputData ioOutputData = getClearlinkInputs(clearlinkRepresentation.input);

	bool inputValue = ioOutputData.getDigitalInputValue(requestedInput);

	eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
      << "Has value " << std::to_string(inputValue) << std::flush;
}