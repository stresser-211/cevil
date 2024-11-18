#ifndef UTILITY_H
#define UTILITY_H
#include "__internal/preprocessor.hpp"
#include "__internal/global.hpp"
template <typename... T>
void stacktrace(cstr_t _module, T... msg) {
	if (!global::logfile.is_open()) {
		std::cerr << "---Couldn't open \"stacktrace.log\"---" << std::endl;
		return;
	}
	const std::chrono::time_point now = std::chrono::system_clock::now();
	const std::string current_time = std::format("{}", std::chrono::floor<std::chrono::seconds>(now));
	global::logfile << std::format("[{}] [{}] ", current_time, _module);
	((global::logfile << msg << " "), ...);
	global::logfile << std::endl;
}
uint32_t get_CRC(cstr_t filename) {
	uint32_t CRC = 0xFFFFFFFF;
	unsigned char buffer[4096];
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		stacktrace(_module.error, "---Unable to open file:", filename, "---");
		return 0; //todo: exception
	}
	while (file) {
		file.read(reinterpret_cast<str_t>(buffer), 4096);
		for (std::streamsize index = 0, bytes_read = file.gcount(); index < bytes_read; index++) {
			uint8_t byte = buffer[index];
			CRC = (CRC >> 8) ^ global::CRC_table[(CRC ^ byte) & 0xFF];
		}
	}
	return CRC ^ 0xFFFFFFFF;
}
int get_config(void) {
	std::ifstream config("config.cfg", std::ios::in);
	if (!config.is_open()) {
		stacktrace(_module.error, "---Unable to open config file---");
		return 0;
	}
	std::string buffer;
	while (std::getline(config, buffer)) {
		std::string::size_type pos = buffer.find("=");
		std::string key = buffer.substr(0, pos).c_str();
		std::string value = buffer.substr(++pos).c_str();
		auto it = std::find_if(global::config.begin(), global::config.end(),
			[&key](const std::pair<std::string, uint16_t>& pair) {
				return pair.first == key;
			});
		if (it != global::config.end()) {
			it->first = value;
		}
	}
	return 1;
}
#endif /* UTILITY_H */