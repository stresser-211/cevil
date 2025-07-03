#ifndef INTERNAL_OBJECTS_H
#define INTERNAL_OBJECTS_H
#include "../internal/include.hpp"
#include "sdl.hpp"
struct cubic_bezier {
	float x1;
	float y1;
	float x2;
	float y2;
};
constexpr struct {
	cubic_bezier straight{0,0,1,1};
	cubic_bezier ease_in{0.5,0,1,1};
	cubic_bezier ease_out{0,0,0.5,1};
	cubic_bezier ease_inout{0.5,0,0.5,1};
	cubic_bezier elastic_in{1,0.5,1,1};
	cubic_bezier elastic_out{0,0,0,.5};
	cubic_bezier elastic_inout{1,0.5,0,0.5};
	cubic_bezier wave{0.5,1.5,0.5,-0.5};
	cubic_bezier glitch{1,1.25,0,-0.25};
	cubic_bezier exponential_in{1,0,1,1};
	cubic_bezier exponential_out{0,0,0,1};
	cubic_bezier exponential_inout{1,0,0,1};
	cubic_bezier backout{0.72,1.44,0.4,1.28};
	cubic_bezier elastic_backout{1,0.5,0.5,1.5};
	cubic_bezier backout_smack{.9,1.27,0,1.44};
} bezier;
namespace basic {
	extern auto make_window(std::string_view title, Uint16T width, Uint16T height);
	extern auto make_window(std::string_view title);
	class window final {
		using E = gl::ecfg;
		/* --- Construction --- */
		forceinline window(const char* title, auto width, auto height) {
			win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | ((bool)gl::config[E::FSCR].second ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
			(win == nullptr) ? throw std::runtime_error(SDL_GetError()) : void(0);
			rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | ((bool)gl::config[E::VSYNC].second ? SDL_RENDERER_PRESENTVSYNC : 0));
			(rend == nullptr) ? throw std::runtime_error(SDL_GetError()) : void(0);
			SDL_ShowWindow(win);
		}
	public:
		template <typename... T> window(T...) = delete;
		~window(void) noexcept {
			(rend != nullptr) ? SDL_DestroyRenderer(rend) : void(0);
			(win != nullptr) ? SDL_DestroyWindow(win) : void(0);
		}
		friend auto make_window(std::string_view title, Uint16T width, Uint16T height) {
			return window(title.data(), width, height);
		}
		friend auto make_window(std::string_view title) {
			return window(title.data(), gl::config[E::WIDTH].second, gl::config[E::HEIGHT].second);
		}
		/* --- Methods --- */
		void update(void) {
			SDL_RenderPresent(rend);
		}
		void resize(Uint16T width, Uint16T height) {
			SDL_SetWindowSize(win, width, height);
		}
		void msgbox_info(std::string_view message) {
			window msgbox = make_window(message, 800u, 600u);
			//...
		}
		void msgbox_action(std::string_view message) {
			window msgbox = make_window(message, 800u, 600u);
			//...
		}
	private:
		SDL_Window* win;
		SDL_Renderer* rend;
		SDL_GLContext context = SDL_GL_CreateContext(win); //tmp
	};
	class game_object {
		static Uint32T count; /* 18446744073709551615 objects ought to be enough for anybody */ 
	protected:
		SDL_Vertex vertex;
		SDL_Rect hitbox;
		int z;
	public:
		game_object(void) {
			count++;
		}
		~game_object(void) {
			count--;
		}
		virtual void move(int64_t x, int64_t y, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void move(uint32_t step, gl::direction direction, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void rotate(int16_t angle, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void resize(Int16T size, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void resize(Uint16T size, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
	};
	class texture : private game_object {
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
			: game_object()
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
	Uint32T game_object::count;
}
#endif /* INTERNAL_OBJECTS_H */