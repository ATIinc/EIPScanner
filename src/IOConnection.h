//
// Created by flipback on 11/18/19.
//

#ifndef EIPSCANNER_IOCONNECTION_H
#define EIPSCANNER_IOCONNECTION_H

#include <memory>
#include <vector>
#include <functional>
#include "cip/Types.h"
#include "sockets/UDPSocket.h"

namespace eipScanner {
	class ConnectionManager;

	class IOConnection {
		friend class ConnectionManager;
	public:
		using ReceiveDataHandle = std::function<void(cip::CipUdint, cip::CipUint, const std::vector<uint8_t>&)>;
		using CloseHandle = std::function<void()>;

		using WPtr=std::weak_ptr<IOConnection>;
		using SPtr=std::shared_ptr<IOConnection>;

		~IOConnection();

		void setDataToSend(const std::vector<uint8_t>& data);
		void setReceiveDataListener(ReceiveDataHandle handle);
		void setCloseListener(CloseHandle handle);

	private:
		IOConnection();
		void notifyReceiveData(const std::vector<uint8_t> &data);
		bool notifyTick(std::chrono::milliseconds period);

		cip::CipUdint _o2tNetworkConnectionId;
		cip::CipUdint _t2oNetworkConnectionId;
		cip::CipUdint _o2tAPI;
		cip::CipUdint _t2oAPI;

		cip::CipUdint _o2tTimer;
		cip::CipUdint _t2o_timer;

		cip::CipUsint _connectionTimeoutMultiplier;
		cip::CipUdint _connectionTimeoutCount;

		cip::CipUdint _o2tSequenceNumber;
		cip::CipUdint _t2oSequenceNumber;
		cip::CipUdint _serialNumber;

		cip::CipUsint _transportTypeTrigger;
		cip::CipBool  _o2tRealTimeFormat;
		cip::CipBool  _t2oRealTimeFormat;
		cip::CipUint  _sequenceValueCount;
		std::vector<uint8_t> _connectionPath;
		cip::CipUint _originatorVendorId;
		cip::CipUdint _originatorSerialNumber;

		std::vector<uint8_t> _outputData;

		sockets::UDPSocket::WPtr _socket;

		ReceiveDataHandle _receiveDataHandle;
		CloseHandle _closeHandle;
	};
}

#endif  // EIPSCANNER_IOCONNECTION_H
