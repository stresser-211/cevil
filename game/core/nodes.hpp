#pragma once
#include "../internal/include.hpp"
#include "sdl.hpp"
extern "C++" {
	namespace node {
		class API window final {
			forceinline window(const char* title, auto width, auto height, auto flags);
		public:
			template <typename... T> window(T...) = delete;
			~window(void) noexcept;
			friend window API make_window(std::string_view title, Uint16T width, Uint16T height, SDL_WindowFlags flags);
			friend window API make_window(std::string_view title, Uint16T width, Uint16T height);
			friend window API make_window(std::string_view title, SDL_WindowFlags flags);
			friend window API make_window(std::string_view title);
			void update(void);
			void resize(Uint16T width, Uint16T height);
			class msgbox {
			public:
				template <typename... T> msgbox(T...) = delete;
				~msgbox(void) noexcept = default;
				static void info(std::string_view message);
				static void action(std::string_view message);
			};
		private:
			SDL_Window* win;
			SDL_GLContext context;
		};
		window API make_window(std::string_view title, Uint16T width, Uint16T height, SDL_WindowFlags flags);
		window API make_window(std::string_view title, Uint16T width, Uint16T height);
		window API make_window(std::string_view title, SDL_WindowFlags flags);
		window API make_window(std::string_view title);
		class API cell {
			//basic::texture txtr;
			Int64T vertex[6];
			Int64T x, y;
		public:
			template <typename... T> cell(T...) = delete;
		};
	}
}