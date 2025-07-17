#define EXPORT
#include "self.hpp"
uint32_t get_CRC(std::string_view filename) {
	_iobuf* file = std::fopen(filename.data(), "b");
	if (file == NULL) {
		std::string errstr = std::format("Unable to open \"{}\".", filename);
		stacktrace(gl::mod.fail, errstr);
		throw std::runtime_error(errstr);
	}
	uint32_t CRC = 0xFFFFFFFF;
	char buffer[4096];
	while (!feof(file)) {
		size_t bytes_read = std::fread(buffer, 1, sizeof(buffer), file);
		for (size_t index = 0; index < bytes_read; index++) { 
			uint8_t byte = buffer[index];
			CRC = (CRC >> 8) ^ gl::CRC[(CRC ^ byte) & 0xFF];
		}
	}
	return CRC ^ 0xFFFFFFFF;
}
int init_SDL(void) noexcept {
	SDL_SetMainReady();
	if (int code = SDL_Init(SDL_INIT_EVERYTHING) < 0) return code;
	if (int code = TTF_Init() < 0) return 1;
	Mix_Init(MIX_INIT_OGG);
	return 0;
}
extern "C" {
	void get_config(void) {
		_iobuf* config = fopen("Config.txt", "r");
		if (config == NULL) {
			stacktrace(gl::mod.error, "Unable to open the config file. Proceeding with default settings.");
			return;
		}
		char buffer[1024];
		while (!feof(config)) {
			std::fgets(buffer, sizeof(buffer), config);
			if (buffer[0] == '#') {
				continue;
			}
			strtrim(buffer);
			char* token = std::strchr(buffer, '=');
			const char* key = std::strstr(buffer, token);
			const char* value = std::strstr(buffer, token+1);
			stacktrace(gl::mod.core, std::format("tok ~ {} ~ key ~ {} ~ val ~ {}", token, key, value).c_str());
			auto it = std::find_if(gl::config.begin(), gl::config.end(),
				[&key](const std::pair<std::string, uint16_t>& pair) {
					return pair.first == key;
				});
			if (it != gl::config.end()) {
				it->first = value;
			}
		}
	}
	int API init_engine(void) {
		switch (int code = init_SDL()) {
		case 0: break;
		case 1: stacktrace(gl::mod.error, std::format("Couldn't initialize SDL_TTF"));
		default:
			stacktrace(gl::mod.error, std::format("Couldn't initialize SDL: {}", SDL_GetError()));
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
			stacktrace(gl::mod.error, std::format("Couldn't open audio device: {}", Mix_GetError()));
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