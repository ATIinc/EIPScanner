//
// Created by Aleksey Timin on 11/23/19.
//

#ifndef EIPSCANNER_FILEOBJECT_FILEOBJECTSTATE_H
#define EIPSCANNER_FILEOBJECT_FILEOBJECTSTATE_H

#include "SessionInfo.h"
#include "MessageRouter.h"
#include "FileObject.h"
#include "cip/GeneralStatusCodes.h"
#include "utils/Logger.h"

namespace eipScanner {
namespace fileObject {
	const cip::CipUsint FILE_OBJECT_CLASS_ID = 0x37;
	const cip::CipUsint MAX_TRANSFER_SIZE = 255;

	enum class FileObjectAttributesCodes : cip::CipUint {
		STATE = 1,
	};

	enum class FileObjectServiceCodes : cip::CipUint {
		INITIATE_UPLOAD = 0x4B,
		UPLOAD_TRANSFER = 0x4F
	};

	class FileObjectState {
	public:
		using UPtr = std::unique_ptr<FileObjectState>;

		FileObjectState(FileObject &owner, cip::CipUint objectId, MessageRouter::SPtr messageRouter);
		virtual ~FileObjectState();

		virtual void initiateUpload(SessionInfo::SPtr si, EndDownloadHandle handle);
		virtual bool transfer(SessionInfo::SPtr si);

		FileObjectStateCodes getStateCode() const;
		void SyncState(SessionInfo::SPtr si);

	protected:
		void logWithStateName(utils::LogLevel logLevel, const std::string &message) const;
		std::string getStateName() const;

		template <class State, class ... Types>
		void setState(Types ... args) {
			_owner._state = std::make_unique<State>(_owner, _objectId, _messageRouter, args...);
		}

		MessageRouter::SPtr _messageRouter;
		cip::CipUint _objectId;
		FileObjectStateCodes _stateCode;
		FileObject &_owner;
	};
}
}

#endif  // EIPSCANNER_FILEOBJECT_FILEOBJECTSTATE_H
