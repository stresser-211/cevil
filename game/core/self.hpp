#pragma once
#include "../internal/include.hpp"
#include "sdl.hpp"
extern "C" {
	int API init_engine(void);
	void API shutdown_engine(void) noexcept;
}