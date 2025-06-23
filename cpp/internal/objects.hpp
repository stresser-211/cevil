#ifndef INTERNAL_OBJECTS_H
#define INTERNAL_OBJECTS_H
#include "preprocessor.hpp"
#include "serialcocksucker.hpp"
#include "global.hpp"
#include "utility.hpp"
struct cubic_bezier {
	float x1;
	float y1;
	float x2;
	float y2;
};
namespace bezier {
	constexpr cubic_bezier ease_in{0.5,0,1,1};
	constexpr cubic_bezier ease_out{0,0,0.5,1};
	constexpr cubic_bezier ease_inout{0.5,0,0.5,1};
	constexpr cubic_bezier elastic_in{1,0.5,1,1};
	constexpr cubic_bezier elastic_out{0,0,0,.5};
	constexpr cubic_bezier elastic_inout{1,0.5,0,0.5};
	constexpr cubic_bezier wave{0.5,1.5,0.5,-0.5};
	constexpr cubic_bezier glitch{1,1.25,0,-0.25};
	constexpr cubic_bezier exponential_in{1,0,1,1};
	constexpr cubic_bezier exponential_out{0,0,0,1};
	constexpr cubic_bezier exponential_inout{1,0,0,1};
	constexpr cubic_bezier backout{0.72,1.44,0.4,1.28};
	constexpr cubic_bezier elastic_backout{1,0.5,0.5,1.5};
	constexpr cubic_bezier backout_smack{.9,1.27,0,1.44};
}
namespace objects {
	class window final {
		using E = gl::ecfg;
		SDL_Window* win;
		SDL_Renderer* rend;
	public:
		window(void) = delete;
		explicit window(std::string_view title) {
			win = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, E::WIDTH, E::HEIGHT, SDL_WINDOW_OPENGL | ((bool)gl::config[E::FSCR].second ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
			rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | ((bool)gl::config[E::VSYNC].second ? SDL_RENDERER_PRESENTVSYNC : 0));
			SDL_ShowWindow(win);
		}
		~window(void) {
			SDL_DestroyRenderer(rend);
			SDL_DestroyWindow(win);
		}
		void update(void) {
			SDL_RenderPresent(rend);
		}
		SDL_Renderer* get_renderer(void) {
			return rend;
		}
		void msgbox(std::string_view message) {}
	};
	class object {
		static uint_least32_t count;
	protected:
		SDL_Vertex vertex;
		SDL_Rect hitbox;
		int z;
	public:
		object(void) {
			count++;
		}
		~object(void) {
			count--;
		}
		virtual void move(int64_t x, int64_t y, uint16_t time = 0, const cubic_bezier& curve = {0,0,1,1}) = 0;
		virtual void move(uint32_t step, gl::direction direction, uint16_t time = 0, const cubic_bezier& curve = {0,0,1,1}) = 0;
		virtual void rotate(int16_t angle, uint16_t time = 0, const cubic_bezier& curve = {0,0,1,1}) = 0;
		template <typename T> void resize(T, T, T, T) = delete;
		virtual void resize(int16_t size, uint16_t time = 0, const cubic_bezier& curve = {0,0,1,1}) = 0;
		virtual void resize(uint16_t size, uint16_t time = 0, const cubic_bezier& curve = {0,0,1,1}) = 0;
	};
	class texture : private object {
		bool failure;
		SDL_Texture* txtr;
		SDL_Rect area;
		bool blend;
		struct {
			uint16_t hue;
			uint8_t saturation;
			uint8_t visibility;
		} colour;
		uint8_t scale;
		uint16_t angle;
	public:
		texture(void) = delete;
		explicit texture(window& win, std::string_view path, int x = 0, int y = 0, int z = 0, uint8_t scale_percent = 100, uint16_t angle = 0)
			: object()
		{
			float scale = scale_percent / 100;
			txtr = IMG_LoadTexture(win.get_renderer(), path.data());
			if (SDL_QueryTexture(txtr, NULL, NULL, &area.w, &area.h) < 0) {
				stacktrace(gl::mod.error, SDL_GetError());
			}
			area.x = x;
			area.y = y;
			area.w *= scale;
			area.h *= scale;
			this->z = z;
		}
		~texture(void) {
			SDL_DestroyTexture(txtr);
		}
		void stretch(int h = 0, int v = 0) {
			return;
		}
		void crop(unsigned left = 0, unsigned right = 0, unsigned up = 0, unsigned down = 0) {
			return;
		}
		void colmod(uint16_t hue = 0, uint8_t saturation = 0, uint8_t visibility = 0) {
			return;
		}
	};
	class audio_chunk {
		Mix_Chunk* chunk;
	public:
		audio_chunk(void) = delete;
		explicit audio_chunk(std::string_view path) {
			if (!(chunk = Mix_LoadWAV(path.data()))) {
				stacktrace(gl::mod.error, std::format("---Couldn't load audio file: {}---", SDL_GetError()).c_str());
			}
		}
	};
	uint_least32_t object::count = 0;
}
#endif /* INTERNAL_OBJECTS_H */