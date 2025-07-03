#define EXPORT
#include "self.hpp"
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
			trim(buffer);
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
	API int init_engine(void) {
		if (Mix_OpenAudio(44100, AUDIO_S16, 2, 2048) < 0) {
			stacktrace(gl::mod.error, "Couldn't open audio device.");
			return 1;
		}
		return 0;
	}
}