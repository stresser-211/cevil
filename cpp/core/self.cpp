#define EXPORT
#include "self.hpp"
extern inline void get_config(void) {
	_iobuf* config = fopen("Config.txt", "r");
	if (config == NULL) {
		stacktrace(gl::mod.error, "Unable to open the config file. Proceeding with default settings.");
		return;
	}
	char buffer[1024];
	while (!feof(config)) {
		std::fgets(buffer, sizeof(buffer), config);
		if (buffer[0] == ';' || buffer[0] == '#') {
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