#pragma once
#include "../internal/include"
#include "sdl.hpp"
extern "C" {
	int API init_engine(void);
	void API shutdown_engine(void) noexcept;
	void API get_config(void);
}