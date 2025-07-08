#ifndef INTERNAL_OBJECTS_H
#define INTERNAL_OBJECTS_H
#include "../internal/include.hpp"
#include "sdl.hpp"
static constinit std::array<std::ranges::iota_view<uint64_t, uint64_t>, 7> layer = {
	std::ranges::views::iota(1ull, ULONG_LONG_MAX / 6),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 + 1, ULONG_LONG_MAX / 6 * 2),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 2 + 1, ULONG_LONG_MAX / 6 * 3),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 3 + 1, ULONG_LONG_MAX / 6 * 4),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 4 + 1, ULONG_LONG_MAX / 6 * 5),
	std::ranges::views::iota(ULONG_LONG_MAX / 6 * 5, ULONG_LONG_MAX)
};
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
		gl::elayer layer;
	protected:
		[[maybe_unused]] SDL_Vertex vertex;
		[[maybe_unused]] SDL_Rect hitbox;
		Int64T x, y;
		Uint64T z;
		interface(void) {
			count++;
		}
		virtual ~interface(void) {
			count--;
		}
	public:
		/* --- No default arguments in the implementation please. --- */
		virtual void move(Int64T x, Int64T y, Uint16T time = 0u, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void move(Uint32T step, gl::direction direction, Uint16T time = 0u, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void rotate(Int16T angle, Uint16T time = 0u, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void resize(Int16T size, Uint16T time = 0u, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void resize(Uint16T size, Uint16T time = 0u, const cubic_bezier& curve = bezier::straight) = 0;
		virtual void destroy(void) = 0;
	};
	class texture : private interface {
		SDL_Texture* txtr;
		SDL_Rect area;
		gl::blend blend;
		struct {
			Uint16T hue;
			Uint8T saturation;
			Uint8T visibility;
		} colour;
		Uint8T scale;
		Uint16T angle;
	public:
		template <typename... T> texture(T...) = delete;
		explicit texture(window& win, std::string_view path, Int32T x = 0, Int32T y = 0, Uint8T scale_percent = 100u, Uint16T angle = 0u) : interface() {
			float scale = scale_percent / 100;
			txtr = IMG_LoadTexture(nullptr, path.data());
			if (SDL_QueryTexture(txtr, NULL, NULL, &area.w, &area.h) < 0) {
				stacktrace(gl::mod.error, SDL_GetError());
			}
			area.x = x;
			area.y = y;
			area.w *= scale;
			area.h *= scale;
			hitbox = area;
		}
		virtual ~texture(void) {
			SDL_DestroyTexture(txtr);
		}
		virtual void stretch(int h = 0, int v = 0) final {
			return;
		}
		virtual void crop(unsigned left = 0, unsigned right = 0, unsigned up = 0, unsigned down = 0) final {
			return;
		}
		virtual void colmod(uint16_t hue = 0, uint8_t saturation = 0, uint8_t visibility = 0) final {
			return;
		}
	};
	class audio_chunk {
		Mix_Chunk* chunk;
	public:
		template <typename... T> audio_chunk(T...) = delete;
		explicit audio_chunk(std::string_view path) {
			if (!(chunk = Mix_LoadWAV(path.data()))) {
				stacktrace(gl::mod.error, SDL_GetError());
			}
		}
	};
	Uint64T interface::count;
}
#endif /* INTERNAL_OBJECTS_H */