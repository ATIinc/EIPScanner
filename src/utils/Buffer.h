//
// Created by Aleksey Timin on 11/16/19.
//

#ifndef EIPSCANNER_UTILS_BUFFER_H
#define EIPSCANNER_UTILS_BUFFER_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include "cip/CipString.h"
#include "cip/CipRevision.h"

namespace eipScanner {
namespace utils {
	class Buffer {
	public:
		explicit Buffer(size_t capacity);
		explicit Buffer(const std::vector<uint8_t>& data);
		Buffer();

		Buffer& operator << (uint8_t val);
		Buffer& operator >> (uint8_t& val);

		Buffer& operator << (int8_t val);
		Buffer& operator >> (int8_t& val);

		Buffer& operator << (uint16_t val);
		Buffer& operator >> (uint16_t& val);

		Buffer& operator << (int16_t val);
		Buffer& operator >> (int16_t& val);

		Buffer& operator << (uint32_t val);
		Buffer& operator >> (uint32_t& val);

		Buffer& operator << (int32_t val);
		Buffer& operator >> (int32_t& val);

		Buffer& operator << (float val);
		Buffer& operator >> (float & val);

		Buffer& operator << (double val);
		Buffer& operator >> (double& val);

		Buffer& operator << (const std::vector<uint8_t>& val);
		Buffer& operator >> (std::vector<uint8_t>& val);

		Buffer& operator << (const std::vector<uint16_t>& val);
		Buffer& operator >> (std::vector<uint16_t>& val);

		template <typename T>
		utils::Buffer& operator<<(const cip::CipBaseString<T>& cipSting) {
			return *this << cipSting.getLength() << cipSting.getData();
		}

		template <typename T>
		utils::Buffer& operator>>(cip::CipBaseString<T>& cipSting) {
			T length = 0;
			*this >> length;
			std::vector<uint8_t> data(length);
			*this >> data;

			cipSting = cip::CipBaseString<T>(data);
			return *this;
		}

		Buffer& operator << (cip::CipRevision v);
		Buffer& operator >> (cip::CipRevision & val);

		std::vector<uint8_t> data() const { return _buffer; }
		size_t size() const { return _buffer.size(); }
		size_t pos() const { return _position; }
		bool isValid() const { return _position <= _buffer.size(); }
		bool empty() const  { return  _position >= _buffer.size(); }
	private:
		std::vector<uint8_t> _buffer;
		size_t _position;
	};
}
}
#endif  // EIPSCANNER_BUFFER_H
