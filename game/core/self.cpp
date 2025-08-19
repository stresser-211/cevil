#define EXPORT
#include "self.hpp"
uint32_t get_CRC(std::string_view filename) {
	_iobuf* file = std::fopen(filename.data(), "b");
	if (file == nullptr) {
		stacktrace(MODULE::SYSTEM, ERROR::MISSING_COMPONENT, "filename=", strquoted(filename));
		throw ERROR::MISSING_COMPONENT;
	}
	uint32_t CRC = 0xFFFFFFFF;
	char buffer[4096];
	while (!std::feof(file)) {
		size_t bytes_read = std::fread(buffer, 1, sizeof(buffer), file);
		for (size_t index = 0; index < bytes_read; index++) { 
			uint8_t byte = buffer[index];
			CRC = (CRC >> 8) ^ CRC_table[(CRC ^ byte) & 0xFF];
		}
	}
	return CRC ^ 0xFFFFFFFF;
}
int init_SDL(void) noexcept {
	SDL_SetMainReady();
	if (int code = SDL_Init(SDL_INIT_EVERYTHING); code < 0) return code;
	if (int code = TTF_Init(); code < 0) return 1;
	Mix_Init(MIX_INIT_OGG);
	return 0;
}
extern "C" {
	void get_config(void) {
		_iobuf* config = fopen("./Config.txt", "r");
		if (config == nullptr) {
			stacktrace(MODULE::SYSTEM, ERROR::CONFIG_NOT_OPENED);
			return;
		}
		while (!std::feof(config)) {
			std::string buffer(100, '\0');
			std::fgets(buffer.data(), buffer.length(), config);
			if (buffer[0] == '#') continue;
			strsanitize(buffer);
			int token = buffer.find('=');
			if (token == -1) {
				stacktrace(MODULE::SYSTEM, ERROR::TOKEN_NOT_FOUND);
				continue;
			}
			std::string key = buffer.substr(0, token);
			std::string value = buffer.substr(token + 1);
			auto it = std::ranges::find_if(
				::config,
				[&key](const auto& pair) {
					return pair.first == key;
				}
			);
			if (it == ::config.end()) {
				stacktrace(MODULE::SYSTEM, ERROR::CFG_INVALID_ENTRY);
				continue;
			}
			int value_int;
			if (value == "FALSE") {
				value_int = 0;
			} else if (value == "TRUE") {
				value_int = 1;
			} else {
				try {
					value_int = std::stoi(value);
				} catch (std::invalid_argument) {
					stacktrace(MODULE::SYSTEM, ERROR::CFG_INVALID_ARGUMENT, "Note: expected \"TRUE\", \"FALSE\", or an integer.");
					continue;
				}
			}
			it->second = value_int;
		}
	}
	int API init_engine(void) {
		switch (int code = init_SDL()) {
		case 0: break;
		case 1: stacktrace(MODULE::SYSTEM, ERROR::TTF_NOT_INITIALIZED, TTF_GetError());
		default:
			stacktrace(MODULE::SYSTEM, ERROR::SDL_NOT_INITIALIZED, SDL_GetError());
			return code;
		}
		int glmj, glmn;
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &glmj);
		SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &glmn);
		if (glmj > 4) if (glmn > 0) return 2;
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
		if (int code = Mix_OpenAudio(44100, AUDIO_S16, 2, 2048); code < 0) {
			stacktrace(MODULE::ASIO, ERROR::AUDIO_DEVICE_NOT_OPENED, Mix_GetError());
			return code;
		}
		return 0;
	}
	void API shutdown_engine(void) noexcept {
		TTF_Quit();
		Mix_Quit();
		SDL_Quit();
	}
}