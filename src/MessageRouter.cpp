//
// Created by Aleksey Timin on 11/16/19.
//

#include <cassert>
#include "eip/EncapsPacketFactory.h"
#include "utils/Buffer.h"
#include "MessageRouter.h"
#include "cip/MessageRouterRequest.h"
#include "cip/MessageRouterResponse.h"
#include "eip/CommonPacketItemFactory.h"
#include "eip/CommonPacket.h"
#include "utils/Buffer.h"
#include "utils/Logger.h"

namespace eipScanner {
	using namespace cip;
	using namespace utils;
	using eip::CommonPacketItemFactory;
	using eip::CommonPacket;
	using eip::EncapsPacket;
	using eip::EncapsPacketFactory;

	MessageRouter::MessageRouter() = default;

	MessageRouter::~MessageRouter() = default;

	MessageRouterResponse
	MessageRouter::sendRequest(SessionInfo::SPtr si, CipUsint service, const EPath &path,
							   const std::vector<uint8_t> &data) const {
		assert(si);

		Logger(LogLevel::INFO) << "Send request: service=0x" << std::hex << static_cast<int>(service)
			<< " epath=" << path.toString();

		MessageRouterRequest request{service, path, data};

		CommonPacketItemFactory commonPacketItemFactory;
		CommonPacket commonPacket;
		commonPacket << commonPacketItemFactory.createNullAddressItem();
		commonPacket << commonPacketItemFactory.createUnconnectedDataItem(request.pack());

		auto packetToSend = EncapsPacketFactory()
				.createSendRRDataPacket(si->getSessionHandle(), 0, commonPacket.pack());

		auto receivedPacket = si->sendAndReceive(packetToSend);

		Buffer buffer(receivedPacket.getData());
		cip::CipUdint interfaceHandle = 0;
		cip::CipUint timeout = 0;
		std::vector<uint8_t> receivedData(receivedPacket.getData().size() - 6);

		buffer >> interfaceHandle >> timeout >> receivedData;

		commonPacket.expand(receivedData);

		MessageRouterResponse response;
		response.expand(commonPacket[1].getData());

		return response;
	}
}