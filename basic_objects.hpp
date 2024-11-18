#ifndef BASIC_OBJECTS_H
#define BASIC_OBJECTS_H
#include "__internal/preprocessor.hpp"
#include "__internal/types.hpp"
#include "__internal/global.hpp"
class texture {
	SDL_Texture* txtr;
	SDL_Rect rect;
	SDL_Renderer* rend;
	bool is_transparent;
	struct {
		uint16_t hue;
		uint8_t saturation;
		uint8_t visibility;
	} colour;
	int x;
	int y;
	uint8_t scale;
	uint16_t angle;
public:
	texture(SDL_Renderer* rend, cstr_t path, int x = 0, int y = 0, uint8_t scale = 100, uint16_t angle = 0)
		: rend(rend), x(x), y(y), scale(scale), angle(angle)
	{
		if (!(txtr = IMG_LoadTexture(rend, path))) {
			txtr = nullptr;
		}
	}
	~texture(void) {
		SDL_DestroyTexture(txtr);
	}
	void stretch(int left = 0, int right = 0, int up = 0, int down = 0) {
		return;
	}
	void crop(unsigned int left = 0, unsigned int right = 0, unsigned int up = 0, unsigned int down = 0) {
		return;
	}
	void colmod(unsigned int hue = 0, unsigned int saturation = 0, unsigned int visibility = 0) {
		return;
	}
};
class window {
	SDL_Window* win;
	SDL_Renderer* rend;
public:
	window(cstr_t title) {
		auto flags =  SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS;
		using cfg = global::e_config;
		if (global::config[cfg::fullscreen].second == 1) {
			flags |= SDL_WINDOW_FULLSCREEN;
		}
		win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, global::config[cfg::width].second, global::config[cfg::height].second, flags);
		rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	}
	~window(void) {
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(win);
	}
	void render(void) {
		return;
	}
	void rerender(void) {
		return;
	}
	auto get_renderer(void) const {
		return rend;
	}
};
#endif /* BASIC_OBJECTS_H */