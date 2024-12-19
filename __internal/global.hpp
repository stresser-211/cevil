#ifndef GLOBAL_H
#define GLOBAL_H
#include "preprocessor.hpp"
constexpr struct {
	const char* core = "CORE";
	const char* warn = "WARNING";
	const char* error = "ERROR";
	const char* audio = "AUDIO";
	const char* render = "RENDER";
	const char* ios = "I/O";
} _module;
namespace global {
	std::fstream logfile("../stacktrace.log", std::ios::in | std::ios::app);
	constexpr std::array<uint32_t, 256> CRC_table = [](void) {
		uint32_t CRC;
		std::array<uint32_t, 256> table = {};
		for (uint32_t index = 0; index < 256; index++) {
			CRC = index;
			for (uint32_t jndex = 8; jndex > 0; jndex--) {
				if (CRC & 1) {
					CRC = (CRC >> 1) ^ 0xEDB88320;
				} else {
					CRC >>= 1;
				}
			}
			table[index] = CRC;
		}
		return table;
	}();
	constinit std::array<std::pair<std::string, uint16_t>, 7> config = {
		std::make_pair("FPS", 60),
		std::make_pair("VSYNC", 0),
		std::make_pair("FULLSCREEN", 1),
		std::make_pair("WIDTH", 1280),
		std::make_pair("HEIGHT", 720),
		std::make_pair("SHADERS", 1),
		std::make_pair("LDM", 0) /* low detail mode */
	};
	namespace enums {
		enum config {
			fps,
			vsync,
			fullscreen,
			width,
			height,
			shaders,
			ldm
		};
		enum audio_effects {
			no_effect,
			lowpass
		};
	}
}
#endif /* GLOBAL_H */