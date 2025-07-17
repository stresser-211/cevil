#define EXPORT
#include "nodes.hpp"
extern "C++" {
	namespace node {
		window::window(const char* title, auto width, auto height, auto flags) {
			win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | flags);
			if (win == nullptr) throw std::runtime_error(SDL_GetError());
			context = SDL_GL_CreateContext(win);
			SDL_GL_MakeCurrent(win, context);
			SDL_ShowWindow(win);
		}
		window::~window(void) noexcept {
			if (win != nullptr) SDL_DestroyWindow(win);
		}
		window API make_window(std::string_view title, Uint16T width, Uint16T height, SDL_WindowFlags flags) {
			return window(title.data(), width, height, flags);
		}
		window API make_window(std::string_view title, Uint16T width, Uint16T height) {
			using namespace gl;
			return window(title.data(), width, height, ((bool)config[ecfg::FSCR].second ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
		}
		window API make_window(std::string_view title, SDL_WindowFlags flags) {
			using namespace gl;
			return window(title.data(), config[ecfg::WIDTH].second, config[ecfg::HEIGHT].second, flags);
		}
		window API make_window(std::string_view title) {
			using namespace gl;
			return window(title.data(), config[ecfg::WIDTH].second, config[ecfg::HEIGHT].second, ((bool)config[ecfg::FSCR].second ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_BORDERLESS));
		}
		void window::update(void) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			SDL_GL_SwapWindow(win);
		}
		void window::resize(Uint16T width, Uint16T height) {
			SDL_SetWindowSize(win, width, height);
		}
		void window::msgbox::info(std::string_view message) {
			window msgbox = make_window(message, 800u, 600u);
			//...
		}
		void window::msgbox::action(std::string_view message) {
			window msgbox = make_window(message, 800u, 600u);
			//...
		}
	}
}