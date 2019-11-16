//
// Created by Aleksey Timin on 11/16/19.
//

#include <eip/EncapsPacketFactory.h>
#include <utils/Buffer.h>
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

	MessageRouterResponse
	MessageRouter::sendRequest(SessionInfo::SPtr si, ServiceCodes service, const EPath &path,
							   const std::vector<uint8_t> &data) {


		Logger(LogLevel::INFO) << "Send request: service=" << service
			<< " epath=" << path.toString();

		MessageRouterRequest request{service, path, data};

		CommonPacketItemFactory commonPacketItemFactory;
		CommonPacket commonPacket;
		commonPacket << commonPacketItemFactory.createNullAddressItem();
		commonPacket << commonPacketItemFactory.createUnconnectedDataItem(request.pack());

		auto packetToSend = EncapsPacketFactory()
				.createSendRRDataPacket(si->getSessionHandle(), 0, commonPacket.pack());

		auto receivedPacket = si->sendAndReceive(packetToSend);
		// TODO: Add checks for received data

		Buffer buffer(receivedPacket.getData());
		cip::CipUdint interfaceHandle;
		cip::CipUint timeout;
		std::vector<uint8_t> receivedData(receivedPacket.getData().size() - 6);

		buffer >> interfaceHandle >> timeout >> receivedData;

		commonPacket.expand(receivedData);

		MessageRouterResponse response;
		response.expand(commonPacket[1].getData());

		return response;
	}
}