#ifndef INTERNAL_GLOBAL_H
#define INTERNAL_GLOBAL_H
#include "preprocessor.hpp"
namespace gl {
	constinit bool nolog{false};
	constexpr struct {
		const char* core = "CORE";
		const char* warn = "WARNING";
		const char* error = "ERROR";
		const char* fail = "FAILURE";
		const char* render = "RENDER";
		const char* asio = "AUDIO";
		const char* mem = "MEMORY";
	} mod;
	constexpr std::array<uint32_t, 256> CRC = [](void) {
		uint32_t _CRC;
		std::array<uint32_t, 256> table = {};
		for (uint16_t index = 0; index < 256; index++) {
			_CRC = index;
			for (char jndex = 8; jndex > 0; jndex--) {
				if (_CRC & 1) {
					_CRC = (_CRC >> 1) ^ 0xEDB88320;
				} else {
					_CRC >>= 1;
				}
			}
			table[index] = _CRC;
		}
		return table;
	}();
	constinit std::array<std::pair<const char*, uint16_t>, 7> config = {
		std::make_pair("FPS", 60),
		std::make_pair("VSYNC", 0),
		std::make_pair("FULLSCREEN", 1),
		std::make_pair("WIDTH", 1280),
		std::make_pair("HEIGHT", 720),
		std::make_pair("SHADERS", 1),
		std::make_pair("LDM", 0)
	};
	enum ecfg {
		FPS, VSYNC, FSCR, WIDTH, HEIGHT, SHADERS, LDM
	};
	enum direction {
		UP, DOWN, LEFT, RIGHT, FRONT, BACK
	};
}
#endif /* INTERNAL_GLOBAL_H */