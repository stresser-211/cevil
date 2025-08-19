#pragma once
#include "preprocessor.hpp"
enum struct CFG {
	FPS, VSYNC, FSCR, WIDTH, HEIGHT, SHADERS, LDM
};
enum struct DIRECTION {
	UP, DOWN, LEFT, RIGHT, FRONT, BACK
};
enum struct BLENDING {
	NORMAL, MULTIPLY, SCREEN, LINLIGHT, INVERT
};
enum struct LAYER {
	HIDDEN, MAP, OBJECT, INFO, POPUP, INTERFACE
};
enum struct MODULE {
	SYSTEM, GAME, RENDER, ASIO, MEMORY, NETWORK
};
enum struct LOGLEVEL {
	SYSTEM, ERROR, WARNING, INFO, VERBOSE
};
enum struct ERROR {
	/* Not error */
	INFO_STARTUP = -9999,
	INFO_SHUTDOWN,
	INFO_GAME_STARTED,
	/* External */
	OUTDATED_OPENGL = -999,
	SDL_NOT_INITIALIZED,
	TTF_NOT_INITIALIZED,
	AUDIO_DEVICE_NOT_OPENED,
	/* Internal */
	INVALID_MODULE = 0,
	MISSING_COMPONENT,
	CONFIG_NOT_OPENED,
	CFG_INVALID_ENTRY,
	CFG_INVALID_ARGUMENT,
	UNHANDLED_EXCEPTION,
	INIT_FAILURE,
	/* Domain */
	OVERFLOW = 100,
	DIVISION_BY_ZERO,
	TOKEN_NOT_FOUND
};
inline constinit LOGLEVEL loglevel = LOGLEVEL::VERBOSE; //LOGLEVEL::WARNING;
inline const std::map<ERROR, std::pair<LOGLEVEL, std::string>> ERRSTR = {
	/* SYSTEM */
	{ ERROR::OUTDATED_OPENGL, std::make_pair(LOGLEVEL::SYSTEM, "Unable to start: the program requires OpenGL 4.0+ to run.") },
	{ ERROR::INVALID_MODULE, std::make_pair(LOGLEVEL::SYSTEM, "Invalid module.") },
	{ ERROR::MISSING_COMPONENT, std::make_pair(LOGLEVEL::SYSTEM, "A critical system component is missing.") },
	{ ERROR::TTF_NOT_INITIALIZED, std::make_pair(LOGLEVEL::SYSTEM, "Couldn't initialize SDL_TTF: ") },
	{ ERROR::SDL_NOT_INITIALIZED, std::make_pair(LOGLEVEL::SYSTEM, "Couldn't initialize SDL: ") },
	{ ERROR::AUDIO_DEVICE_NOT_OPENED, std::make_pair(LOGLEVEL::SYSTEM, "Couldn't open audio device: ") },
	{ ERROR::INIT_FAILURE, std::make_pair(LOGLEVEL::SYSTEM, "Initialization failure") },
	{ ERROR::UNHANDLED_EXCEPTION, std::make_pair(LOGLEVEL::SYSTEM, "An unhandled exception occured.") },
	/* ERROR */
	{ ERROR::DIVISION_BY_ZERO, std::make_pair(LOGLEVEL::ERROR, "Division by zero is undefined.") },
	{ ERROR::OVERFLOW, std::make_pair(LOGLEVEL::ERROR, "Attempt to assign a value results in an overflow.") },
	/* WARNING */
	{ ERROR::CONFIG_NOT_OPENED, std::make_pair(LOGLEVEL::WARNING, "Unable to open the config file. Proceeding with default settings.") },
	{ ERROR::TOKEN_NOT_FOUND, std::make_pair(LOGLEVEL::WARNING, "Token not found. Entry skipped.") },
	{ ERROR::CFG_INVALID_ENTRY, std::make_pair(LOGLEVEL::WARNING, "Invalid config entry. Skipped.") },
	{ ERROR::CFG_INVALID_ARGUMENT, std::make_pair(LOGLEVEL::WARNING, "Invalid argument for the config entry. Skipped.") },
	/* INFO */
	{ ERROR::INFO_STARTUP, std::make_pair(LOGLEVEL::INFO, "Initialization started.") },
	{ ERROR::INFO_SHUTDOWN, std::make_pair(LOGLEVEL::INFO, "Shutting down.") },
	{ ERROR::INFO_GAME_STARTED, std::make_pair(LOGLEVEL::INFO, "Game started!") }
};
inline constinit std::array<std::pair<const char*, uint16_t>, 7> config = {
	std::make_pair("FPS", 60),
	std::make_pair("VSYNC", 0),
	std::make_pair("FULLSCREEN", 1),
	std::make_pair("WIDTH", 1280),
	std::make_pair("HEIGHT", 720),
	std::make_pair("SHADERS", 1),
	std::make_pair("LDM", 0)
};
inline constexpr std::array<uint32_t, 256> CRC_table = [] noexcept {
	uint32_t CRC;
	std::array<uint32_t, 256> table = {};
	for (uint16_t index = 0; index < 256; index++) {
		CRC = index;
		for (char jndex = 8; jndex > 0; jndex--) {
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