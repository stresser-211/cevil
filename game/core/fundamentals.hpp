#pragma once
#include "../internal/include.hpp"
#include "sdl.hpp"
struct cubic_bezier {
	float x1, y1, x2, y2;
};
constexpr struct bezier {
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
extern "C++" {
	namespace basic {
		class interface {
			static Uint64T count; /* 18446744073709551615 objects ought to be enough for anybody */ 
			gl::elayer layer;
		protected:
			[[maybe_unused]] SDL_Vertex vertex;
			[[maybe_unused]] SDL_Rect hitbox;
			Int64T x, y;
			Uint64T z;
			interface(void);
			virtual ~interface(void);
		public:
			/* --- No default arguments in derived classes please. --- */
			virtual void move(Int64T x, Int64T y, Uint16T time = 0u, const cubic_bezier& curve = bezier.straight) = 0;
			virtual void move(Uint32T step, gl::direction direction, Uint16T time = 0u, const cubic_bezier& curve = bezier.straight) = 0;
			virtual void rotate(Int16T angle, Uint16T time = 0u, const cubic_bezier& curve = bezier.straight) = 0;
			virtual void resize(Int16T size, Uint16T time = 0u, const cubic_bezier& curve = bezier.straight) = 0;
			virtual void resize(Uint16T size, Uint16T time = 0u, const cubic_bezier& curve = bezier.straight) = 0;
			virtual void destroy(void) = 0;
		};
		class texture : private interface {
			bool invalid;
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
			texture(std::string_view path, Int32T x = 0, Int32T y = 0, Uint8T scale_percent = 100u, Uint16T angle = 0u);
			virtual ~texture(void);
			virtual void stretch(int h = 0, int v = 0) final;
			virtual void crop(unsigned left = 0, unsigned right = 0, unsigned up = 0, unsigned down = 0) final;
			virtual void colmod(uint16_t hue = 0, uint8_t saturation = 0, uint8_t visibility = 0) final;
		};
		class audio_chunk {
			Mix_Chunk* chunk;
		public:
			template <typename... T> audio_chunk(T...) = delete;
			audio_chunk(std::string_view path);
		};
	}
}