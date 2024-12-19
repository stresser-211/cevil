#ifndef INTERNAL_OBJECTS_H
#define INTERNAL_OBJECTS_H
#include "preprocessor.hpp"
#include "global.hpp"
namespace window {
	class _base {
	protected:
		SDL_Window* win;
		_base(void) = default;
		explicit _base(std::string_view title) {
			using cfg = global::enums::config;
			int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS;
			if (global::config[cfg::fullscreen].second == 1) {
				flags |= SDL_WINDOW_FULLSCREEN;
			}
			win = SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, global::config[cfg::width].second, global::config[cfg::height].second, flags);
		};
		virtual ~_base(void) {
			SDL_DestroyWindow(win);
		};
		virtual void show(void) = 0;
	};
	class native final : private _base {
		SDL_Renderer* rend;
	public:
		native(void) = delete;
		explicit native(std::string_view title) : _base(title) {
			rend = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
		}
		~native(void) {
			SDL_DestroyRenderer(rend);
		}
		void show(void) override {
			SDL_RenderClear(rend);
			SDL_RenderPresent(rend);
		}
	};
	class pop_up final : private _base {
		std::string_view message;
	public:
		explicit pop_up(std::string_view message) : _base(message) {
			this->message = message;
		}
		pop_up(void) : pop_up("---No message set yet---")
		{
		}
		void operator=(std::string_view message) {
			this->message = message;
		}
		~pop_up(void) = default;
		void show(void) override {
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "pop", message.data(), win);
		};
	};
};
namespace basic_objects {
	using namespace global;
	class texture {
		SDL_Texture* txtr;
		SDL_Rect rect;
		SDL_Renderer* rend;
		bool blending;
		struct {
			uint16_t hue;
			uint8_t saturation;
			uint8_t visibility;
		} colour;
		uint8_t scale;
		uint16_t angle;
	public:
		texture(void) = delete;
		explicit texture(SDL_Renderer* rend, std::string_view path, int x = 0, int y = 0, uint8_t scale = 100, uint16_t angle = 0)
			: rend(rend), scale(scale > 100 ? 100 : scale), angle(angle > 360 ? 360 : angle)
		{
			if ((txtr = IMG_LoadTexture(rend, path.data()))) {
				SDL_QueryTexture(txtr, NULL, NULL, &rect.h, &rect.w);
				rect.x = x;
				rect.y = y;
				return;
			}
			txtr = nullptr;
		}
		~texture(void) {
			SDL_DestroyTexture(txtr);
		}
		void stretch(int h = 0, int v = 0) {
			return;
		}
		void crop(unsigned int left = 0, unsigned int right = 0, unsigned int up = 0, unsigned int down = 0) {
			return;
		}
		void colmod(unsigned int hue = 0, unsigned int saturation = 0, unsigned int visibility = 0) {
			return;
		}
	};
	class audio_device {
		Mix_Chunk* chunk;
	public:
		audio_device(void) = delete;
		explicit audio_device(std::string_view path) {
		}
	};
}
#endif /* INTERNAL_OBJECTS_H */