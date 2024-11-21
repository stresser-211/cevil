#ifndef BASIC_OBJECTS_H
#define BASIC_OBJECTS_H
#include "__internal/preprocessor.hpp"
#include "__internal/objects.hpp"
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
#endif /* BASIC_OBJECTS_H */