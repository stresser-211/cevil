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
namespace bezier {
	constexpr cubic_bezier straight{0,0,1,1};
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
namespace basic {
	extern auto make_window(std::string_view title, Uint16T width, Uint16T height);
	extern auto make_window(std::string_view title);
	class window final {
		using E = gl::ecfg;
		/* --- Construction --- */
		forceinline window(const char* title, auto width, auto height, auto flags) {
			win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | flags);
			if (win == nullptr) throw std::runtime_error(SDL_GetError());
			rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | (static_cast<bool>(gl::config[E::VSYNC].second) ? SDL_RENDERER_PRESENTVSYNC : 0));
			if (rend == nullptr) throw std::runtime_error(SDL_GetError());
			SDL_ShowWindow(win);
		}
	public:
		template <typename... T> window(T...) = delete;
		~window(void) noexcept {
			if (rend != nullptr) SDL_DestroyRenderer(rend);
			if (win != nullptr) SDL_DestroyWindow(win);
		}
		friend auto make_window(std::string_view title, Uint16T width, Uint16T height, SDL_WindowFlags flags) {
			return window(title.data(), width, height, flags);
		}
		friend auto make_window(std::string_view title, Uint16T width, Uint16T height) {
			return window(title.data(), width, height, ((bool)gl::config[E::FSCR].second ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
		}
		friend auto make_window(std::string_view title, SDL_WindowFlags flags) {
			return window(title.data(), gl::config[E::WIDTH].second, gl::config[E::HEIGHT].second, flags);
		}
		friend auto make_window(std::string_view title) {
			return window(title.data(), gl::config[E::WIDTH].second, gl::config[E::HEIGHT].second, ((bool)gl::config[E::FSCR].second ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
		}
		/* --- Methods --- */
		void update(void) {
			SDL_RenderPresent(rend);
		}
		void resize(Uint16T width, Uint16T height) {
			SDL_SetWindowSize(win, width, height);
		}
		class msgbox {
		public:
			template <typename... T> msgbox(T...) = delete;
			~msgbox(void) = default;
			static void info(std::string_view message) {
				window msgbox = make_window(message, 800u, 600u);
				//...
			}
			static void action(std::string_view message) {
				window msgbox = make_window(message, 800u, 600u);
				//...
			}
		};
	private:
		SDL_Window* win;
		SDL_Renderer* rend;
		SDL_GLContext context = SDL_GL_CreateContext(win); //tmp
	};
	class interface {
		static Uint64T count; /* 18446744073709551615 objects ought to be enough for anybody */ 
	protected:
		[[maybe_unused]] SDL_Vertex vertex;
		[[maybe_unused]] SDL_Rect hitbox;
	public:
		interface(void) {
			count++;
		}
		~interface(void) {
			count--;
		}
		virtual void move(int64_t x, int64_t y, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void move(uint32_t step, gl::direction direction, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void rotate(int16_t angle, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void resize(Int16T size, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void resize(Uint16T size, uint16_t time = 0, const cubic_bezier& curve = bezier::straight) = 0;
	};
	class texture : private interface {
		SDL_Texture* txtr;
		SDL_Rect area;
		bool failed;
		gl::blend blend;
		struct {
			uint16_t hue;
			uint8_t saturation;
			uint8_t visibility;
		} colour;
		uint8_t scale;
		uint16_t angle;
	public:
		texture(void) = delete;
		explicit texture(window& win, std::string_view path, int x = 0, int y = 0, uint8_t scale_percent = 100, uint16_t angle = 0) : interface() {
			float scale = scale_percent / 100;
			txtr = IMG_LoadTexture(nullptr, path.data());
			if (SDL_QueryTexture(txtr, NULL, NULL, &area.w, &area.h) < 0) {
				stacktrace(gl::mod.error, SDL_GetError());
			}
			area.x = x;
			area.y = y;
			area.w *= scale;
			area.h *= scale;
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
	Uint64T interface::count;
}
#endif /* INTERNAL_OBJECTS_H */