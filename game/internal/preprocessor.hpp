/* --- Do not change anything --- */
#ifndef PREPROCESS_H
#define PREPROCESS_H
#define _CRT_SECURE_NO_WARNINGS
#if !defined(__cplusplus)
#error --- C++ is required ---
#elif __cplusplus < 202400L
#error --- I am using GCC 15, deal with it ---
#endif /* __cplusplus */
#if defined(_MSC_VER)
#define libexport __declspec(dllexport)
#define libimport __declspec(dllimport)
#define forceinline __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define libexport __attribute__((dllexport))
#define libimport __attribute__((dllimport))
#define forceinline __attribute__((always_inline)) inline
#else
#error --- Unsupported compiler i suppose ---
#endif /* compiler */
#ifndef EXPORT
#define API libimport
#else
#define API libexport
#endif /* EXPORT */
#define nodiscard(reason) [[nodiscard(reason)]]
#define restrict __restrict
#define __CONCAT_IMPL(x, y) x##y
#define __CONCAT(x, y) __CONCAT_IMPL(x, y)
#define cleanup(function) auto __CONCAT(__cleaner_, __COUNTER__) = __MakeScopeGuard(function)
template <typename F> struct __ScopeGuard {
	F func;
	__ScopeGuard(F f) : func(f) {}
	~__ScopeGuard() { func(); }
};
template <typename F> inline __ScopeGuard<F> __MakeScopeGuard(F f) {
	return __ScopeGuard<F>(f);
}
/* I/O */
#include <cstdio>
#include <filesystem>
/* Strings */
#include <cstring>
#include <cctype>
#include <string>
#include <string_view>
#include <format>
/* Utility */
#include <cstdlib>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>
/* Math */
#include <cmath>
#include <ratio>
#include <complex>
#include <random>
#include <ranges>
/* Meta */
#include <cstdint>
#include <type_traits>
#include <concepts>
#include <compare>
/* Diagnostics */
#include <system_error>
#include <stdexcept>
#include <source_location>
/* Time */
#include <chrono>
/* Containers */
#include <initializer_list>
#include <array>
#include <valarray>
#include <span>
/* Concurrency */
#include <future>
#include <semaphore>
#endif /* PREPROCESS_H */