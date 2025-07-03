#ifndef INTERNAL_UTILITY_H
#define INTERNAL_UTILITY_H
#include "preprocessor.hpp"
#include "serialcocksucker.hpp"
#include "global.hpp"
extern void stacktrace(const char* component, std::string_view msg) {
	if (gl::nolog) return;
	_iobuf* logfile = std::fopen("../stacktrace.log", "a");
	if (logfile == NULL) {
		throw std::runtime_error("Failed to open \'stacktrace.log\'.");
	}
	const std::chrono::time_point now = std::chrono::system_clock::now();
	std::fprintf(logfile, "%s\n", std::format("[{}] [{}] {}", std::chrono::floor<std::chrono::seconds>(now), component, msg).c_str());
	std::fclose(logfile);
}
extern inline void trim(char* string) noexcept {
	char buffer[1024];
	int out = 0;
	for (int in = 0; in < sizeof(buffer); in++) {
		if (string[in] == '\0') break;
		if (std::isspace((string[in]))) continue;
		buffer[out++] = string[in];
	}
	buffer[out] = '\0';
	string = buffer;
}
#endif /* INTERNAL_UTILITY_H */