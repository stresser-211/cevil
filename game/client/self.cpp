#define EXPORT
#include "self.hpp"
#include <SDL2/SDL_net.h>
constexpr Int16T port = 12701;
extern "C" {
	int API init_client(void) {
		return 0;
	}
}