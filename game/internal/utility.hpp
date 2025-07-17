#pragma once
#include "preprocessor.hpp"
#include "serialcocksucker.hpp"
#include "global.hpp"
inline extern void stacktrace(const char* component, std::string_view msg) {
	if (gl::nolog) return;
	_iobuf* logfile = std::fopen("../stacktrace.log", "a");
	cleanup([&] {
		std::fclose(logfile);
	});
	if (logfile == nullptr) throw std::runtime_error("Failed to open \"stacktrace.log\".");
	const std::chrono::time_point now = std::chrono::system_clock::now();
	std::fprintf(logfile, "%s\n", std::format("[{}] [{}] {}", std::chrono::floor<std::chrono::seconds>(now), component, msg).c_str());
}
forceinline extern void strtrim(char* string) noexcept {
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