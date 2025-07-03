#include "internal/include.hpp"
#include "core/self.hpp"
#include "maploader/self.hpp"
#include "client/self.hpp"
int main(int argc, char** argv) {
	(void)argc; (void)argv;
	stacktrace(gl::mod.core, "Initialization started.");
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		Mix_Init(MIX_INIT_OGG);
		TTF_Init();
	}
	cleanup( [] {
		stacktrace(gl::mod.core, "Shutting down.");
		{
			TTF_Quit();
			Mix_Quit();
			IMG_Quit();
			SDL_Quit();
		}
	});
	switch (int code = init_engine()) {
	case 0:
		break;
	default:
		stacktrace(gl::mod.fail, std::format("Initialization failure {}", code));
		return 0;
	}
	SDL_Event event;
	for (;;) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				return 0;
			}
		}
	}
}