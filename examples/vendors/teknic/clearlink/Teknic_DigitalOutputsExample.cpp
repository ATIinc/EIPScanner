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

clearlink::assembly::output::IOOutputData getClearlinkOutputs(clearlink::OutputAssemblyObject clearlinkOutput)
{
	return clearlinkOutput.getIOOutputData();
}

void setClearlinkOutputs(clearlink::OutputAssemblyObject &clearlinkOutput,
                    			clearlink::assembly::output::IOOutputData  ioOutputData)
{
	clearlinkOutput.setIOOutputData(ioOutputData);
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

  uint8_t outputIndex = 0;
	uint8_t onValue = 0;

  if (argc > 1) {
    outputIndex = std::stoi(argv[1]);
  }

  if (argc > 2) {
    onValue = std::stoi(argv[2]);
  }

	bool isPWM = onValue > 1;

  eipScanner::utils::Logger(eipScanner::utils::LogLevel::INFO)
      << "Setting output " << std::to_string(outputIndex) << " to "
      << (isPWM ? "PWM " + std::to_string(onValue) + " / 256" : (onValue == 1 ? "on" : "off")) << std::flush;

  // Get the clearlinkIO (given a variable IP address and the default
  // Ethernet/IP port)
  ClearlinkIO clearlinkRepresentation =
      createClearlinkIOObjects("172.31.19.10", 0xAF12);

	// Make sure the config is written
	clearlinkRepresentation.config.setAssembly();


	// Initialize the output values
	clearlinkRepresentation.output.getAssembly();

	// Convert to digital output
	IOOutputData::DigitalOutput providedOutput = static_cast<IOOutputData::DigitalOutput>(outputIndex);

	// Set the IO output data
	clearlink::assembly::output::IOOutputData ioOutputData = getClearlinkOutputs(clearlinkRepresentation.output);
	if (isPWM) {
		ioOutputData.setDigitalOutputPWM(providedOutput, onValue);
	}
	else {
		ioOutputData.setDigitalOutputValue(providedOutput, onValue);
	}


	setClearlinkOutputs(clearlinkRepresentation.output, ioOutputData);

	// Actually write the data to the clearlink
	clearlinkRepresentation.output.setAssembly();
}