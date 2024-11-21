#ifndef INTERNAL_OBJECTS_H
#define INTERNAL_OBJECTS_H
namespace window {
	class _base {
	protected:
		SDL_Window* win;
		_base(void) = delete;
		_base(cstr_t title, auto flags) {
			using cfg = global::e_config;
			if (global::config[cfg::fullscreen].second == 1) {
				flags |= SDL_WINDOW_FULLSCREEN;
			}
			win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, global::config[cfg::width]	.second, global::config[cfg::height].second, flags);
			
		}
		virtual ~_base(void) {
			SDL_DestroyWindow(win);
		}
		virtual void show(void) = 0;
	};
	class native : private _base {
		SDL_Renderer* rend;
	public:
		native(void) = delete;
		native(cstr_t title) : _base(title, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS) {
			rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		}
		virtual ~native(void) {
			SDL_DestroyRenderer(rend);
		}
		void show(void) override {
			SDL_RenderClear(rend);
			SDL_RenderPresent(rend);
		}
	};
	class pop_up : private _base {
		pop_up(void) = delete;
	};
};
#endif /* INTERNAL_OBJECTS_H */