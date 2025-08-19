#pragma once
#include "preprocessor.hpp"
#include "global.hpp"
template <typename T, typename U> concept related_to = std::is_base_of<T, U>::value or std::same_as<T, U>;
template <typename T> concept numeral_t = std::is_arithmetic<T>::value && !std::same_as<T, bool>;
template <typename T> concept integer_t = std::is_integral<T>::value && !std::same_as<T, bool>;
template <typename T> concept fraction_t = std::is_floating_point<T>::value;
template <typename T> concept signed_t = integer_t<T> && std::is_signed<T>::value;
template <typename T> concept unsigned_t = integer_t<T> && std::is_unsigned<T>::value;
template <typename... T> extern inline void stacktrace(MODULE component, ERROR error, const T&... additional_info) requires (std::convertible_to<T, std::string_view> && ...) {
	const auto& message = ERRSTR.at(error);
	if (message.first > loglevel) return;
	_iobuf* logfile = std::fopen("../stacktrace.log", "a");
	cleanup([&] noexcept {
		std::fclose(logfile);
	});
	if (logfile == nullptr) return; /* we do not care */
	const std::chrono::time_point now = std::chrono::system_clock::now();
	int size_extra = (0 + ... + std::string(additional_info).length());
	std::string string_extra{'\n'};
	if (size_extra > 0) {
		string_extra.reserve(size_extra + 2);
		(string_extra.append(additional_info), ...);
		string_extra += '\n';
	}
	std::fprintf(
		logfile,
		std::format(
			"[{}] [{}] {}%s",
			std::chrono::floor<std::chrono::seconds>(now),
			[&component] {
				switch (component) {
					case MODULE::SYSTEM: return "SYSTEM";
					case MODULE::GAME: return "GAME";
					case MODULE::RENDER: return "RENDER";
					case MODULE::ASIO: return "ASIO";
					case MODULE::MEMORY: return "MEMORY";
					case MODULE::NETWORK: return "NETWORK";
					[[unlikely]] default: throw ERROR::INVALID_MODULE;
				}
			}(),
			message.second
		).c_str(),
		string_extra.data() 
	);
}
extern forceinline void strsanitize(std::string& string) noexcept {
	string.erase(
		std::ranges::remove_if(
			string,
			[](unsigned char ch) noexcept {
				return std::isspace(ch) || std::iscntrl(ch);
			}
		).begin(),
		string.end()
	);
}
[[nodiscard]] extern forceinline std::string strquoted(std::string_view string) noexcept {
	std::string out;
	out.reserve(string.length() + 2);
	((out = "\"") += string) += "\"";
	return out;
}