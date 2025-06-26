/* --- Do not change anything --- */
#ifndef PREPROCESS_H
#define PREPROCESS_H
#define _CRT_SECURE_NO_WARNINGS
#if !defined(__cplusplus)
#error --- C++ is required ---
#elif __cplusplus < 202400L
#error --- I'm using GCC 15, deal with it ---
#else
#pragma message("--- Building the project ---")
#endif /* __cplusplus */
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
/* Time */
#include <chrono>
/* Containers */
#include <initializer_list>
#include <array>
#include <valarray>
#include <vector>
#include <span>
/* Concurrency */
#include <future>
#include <semaphore>
#if defined(_MSC_VER)
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
#define RESTRICT __restrict
#define FORCEINLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define DLLEXPORT __attribute__((dllexport))
#define DLLIMPORT __attribute__((dllimport))
#define RESTRICT __restrict__
#define FORCEINLINE inline __attribute__((always_inline))
#else
#error --- Unsupported compiler i suppose ---
#endif /* compiler */
#ifndef EXPORT
#define API DLLIMPORT
#else
#define API DLLEXPORT
#endif /* EXPORT */
#endif /* PREPROCESS_H */