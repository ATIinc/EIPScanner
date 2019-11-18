//
// Created by Aleksey Timin on 11/16/19.
//

#ifndef EIPSCANNER_SOCKETS_TCPSOCKET_H
#define EIPSCANNER_SOCKETS_TCPSOCKET_H

#include <vector>
#include <chrono>
#include "BaseSocket.h"

namespace eipScanner {
namespace sockets {
	class TCPSocket : public BaseSocket {
	public:
		TCPSocket(std::string host, int port, size_t bufferSize);
		virtual ~TCPSocket();

		void Send(const std::vector<uint8_t>& data) const override;
		std::vector<uint8_t> Receive(size_t size) override;

	private:
	};
}
}

#endif  // EIPSCANNER_TCPSOCKET_H
