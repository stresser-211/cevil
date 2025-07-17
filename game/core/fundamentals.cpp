#define EXPORT
#include "fundamentals.hpp"
constinit std::array<std::ranges::iota_view<uint64_t, uint64_t>, 6> layer = {
	std::ranges::views::iota(1ull, ULONG_LONG_MAX / 6),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 + 1, ULONG_LONG_MAX / 6 * 2),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 2 + 1, ULONG_LONG_MAX / 6 * 3),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 3 + 1, ULONG_LONG_MAX / 6 * 4),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 4 + 1, ULONG_LONG_MAX / 6 * 5),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 5, ULONG_LONG_MAX)
};
extern "C++" {
	namespace basic {
		Uint64T interface::count;
		interface::interface(void) {
			count++;
		}
		interface::~interface(void) {
			count--;
		}
		texture::texture(std::string_view path, Int32T x, Int32T y, Uint8T scale_percent , Uint16T angle) : interface() {
			invalid = false;
			float scale = scale_percent / 100;
			/*txtr = IMG_LoadTexture(nullptr, path.data());
			if (SDL_QueryTexture(txtr, NULL, NULL, &area.w, &area.h) < 0) {
				stacktrace(gl::mod.error, SDL_GetError());
				invalid = true;
			}*/
			area.x = x;
			area.y = y;
			area.w *= scale;
			area.h *= scale;
			hitbox = area;
		}
		texture::~texture(void) {
			SDL_DestroyTexture(txtr);
		}
		void texture::stretch(int h, int v) {
			//...
		}
		void texture::crop(unsigned left, unsigned right, unsigned up, unsigned down) {
			//...
		}
		void texture::colmod(uint16_t hue, uint8_t saturation, uint8_t visibility) {
			//...
		}
		audio_chunk::audio_chunk(std::string_view path) {
			if (!(chunk = Mix_LoadWAV(path.data()))) {
				stacktrace(gl::mod.error, SDL_GetError());
			}
		}
	}
}