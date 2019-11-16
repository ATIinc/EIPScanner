//
// Created by Aleksey Timin on 11/16/19.
//

#ifndef EIPSCANNER_UTILS_BUFFER_H
#define EIPSCANNER_UTILS_BUFFER_H

#include <cstdint>
#include <vector>

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


		std::vector<uint8_t> data() const { return buffer; }
		size_t size() const { return buffer.size(); }
		size_t pos() const { return _position; }
	private:
		std::vector<uint8_t> buffer;
		size_t _position;
	};
}
}
#endif  // EIPSCANNER_BUFFER_H
