/* ---Do not change anything--- */
#ifndef PREPROCESS_H
#define PREPROCESS_H
#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED
#if !defined(__cplusplus)
#error ---C++ is required---
#elif __cplusplus <= 201703L
#error ---C++20 or higher is required---
#elif __cplusplus >= 202002L && __cplusplus < 202302L
#pragma message("---Warning: the project uses C++26 thus some features may be unstable and not working as intended. Consider updating if possible. (Your Standard: C++20)---")
/* C++20 Bindings */
#define CXX20
#elif __cplusplus >= 202302L && __cplusplus < 202400L
#pragma message("---Warning: the project uses C++26 thus some features may be unstable and not working as intended. Consider updating if possible. (Your Standard: C++23)---")
/* C++23 Bindings */
#define CXX23
#elif __cplusplus >= 202400L
#pragma message("---Building the project---")
#define CXX26
#endif /* __cplusplus */
/* C */
#include <cstdint>
#include <cmath>
/* I/O */
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>
/* Strings */
#include <string>
#include <format>
/* Utility */
#include <utility>
#include <algorithm>
#include <functional>
#include <concepts>
#include <iterator>
#include <ranges>
#include <ratio>
#include <random>
#include <memory>
#include <compare>
/* Time */
#include <chrono>
/* Containers */
#include <array>
#include <vector>
#include <span>
/* Multithreading */
#include <thread>
#include <future>
#include <mutex>
#include <shared_mutex>
#include <atomic>
#include <semaphore>
#include <coroutine>
 /* SDL */
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_net.h>
#if defined(_MSC_VER)
#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)
#define RESTRICT __restrict
#define FORCEINLINE __forceinline
#elif defined(__GNUC__)
#define DLLEXPORT __attribute__((dllexport))
#define DLLIMPORT __attribute__((dllimport))
#define RESTRICT __restrict__
#define FORCEINLINE inline __attribute__((always_inline))
#else
#error ---Unsupported compiler---
#endif /* compiler */
#ifndef EXPORT
#define API DLLIMPORT
#else
#define API DLLEXPORT
#endif /* EXPORT */
#define str_t char*
#define cstr_t const char*
#endif /* PREPROCESS_H */