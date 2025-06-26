#ifndef INTERNAL_UTILITY_H
#define INTERNAL_UTILITY_H
#include "preprocessor.hpp"
#include "serialcocksucker.hpp"
#include "global.hpp"
extern void stacktrace(const char* component, std::string_view msg) {
	if (gl::nolog) return;
	_iobuf* logfile = std::fopen("../stacktrace.log", "a");
	if (logfile == NULL) {
		throw std::runtime_error("stacktrace.log opening failure");
	}
	const std::chrono::time_point now = std::chrono::system_clock::now();
	std::fprintf(logfile, "%s\n", std::format("[{}] [{}] {}", std::chrono::floor<std::chrono::seconds>(now), component, msg).c_str());
	std::fclose(logfile);
}
extern uint32_t get_CRC(std::string_view filename) {
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
static inline void trim(char* string) noexcept {
	char buffer[1024];
	int out = 0;
	for (int in = 0; in < sizeof(buffer); in++) {
		if (string[in] == '\0') {
			break;
		}
		if (std::isspace((string[in]))) {
			continue;
		}
		buffer[out++] = string[in];
	}
	buffer[out] = '\0';
	string = buffer;
}
#endif /* INTERNAL_UTILITY_H */