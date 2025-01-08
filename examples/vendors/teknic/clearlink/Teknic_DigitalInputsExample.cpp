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

/* All of the functions here are based off of the Teknic Documentation.
		Unfortunately most of that is rough around the edges.

	Using the Step & Direction Motor Input Object reference, the requirements could be deduced:
		https://www.teknic.com/files/downloads/clearlink_ethernet-ip_object_reference.pdf#page=41

	The teknic clearlink examples also provide Ladder Logic that steps through the process:
		https://teknic.com/downloads/

	------------------------------------------------------
	
	In brief, there are two types of movements:
		1. Positional Move
		2. Velocity Move

	For both movements
		1. Any outstanding faults need to be cleared
			* There are two types of faults that can occur:
				1. Motor Faults/Alerts
				2. Motor Shutdowns 

		2. The motor must be "Enabled"
			* Command == EIP_OUTPUT->setOutputFlag(SDMotorOutputObject::OutputFlag::Enable, true)
			* NOTE: When the Brake Pin has been set, enabling the motor will also set the brake output

		3. The "Load<Type>Move" bit must be UN-set
			* Positional == EIP_OUTPUT->setOutputFlag(SDMotorOutputObject::OutputFlag::LoadPositionalMove, false)
			* Velocity == EIP_OUTPUT->setOutputFlag(SDMotorOutputObject::OutputFlag::LoadVelocityMove, false)
		
		4. The target must be loaded into the appropriate register
			* Positional == EIP_OUTPUT->setMoveDistance()
			* Velocity == EIP_OUTPUT->setJogVelocity()
		
		5. The "Load<Type>Move" bit must be set 
			* See step 3 for the correct flags

		6. The ACK for the "Load<Type>Move" bit must be read from the Clearlink
			* Command == EIP_INPUT->isInState(SDMotorInputObject::InputState::Load<Type>MoveAck)

		7. The "Load<Type>Move" bit must be UN-set
			* See step 3 for the correct flags

		8. The motor should be UN-Enabled (if motion has stopped)
			* See step 2 for the correct flags
			* NOTE: When the Brake Pin has been set, UN-enabling the motor will also UN-set the brake output
			* NOTE 2: If a non-zero velocity move has been commanded, the motor should stay enabled 
*/


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