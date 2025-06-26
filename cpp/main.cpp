#include "internal/utility.hpp"
#include "core/self.hpp"

int init_engine(void) {
	if (Mix_OpenAudio(44100, AUDIO_S16, 2, 2048) < 0) {
		stacktrace(gl::mod.error, "Couldn't open audio device.");
		return 1;
	}
	return 0;
}

int main(int argc, char** argv) {
	(void)argc; (void)argv;
	stacktrace(gl::mod.core, "Initialization started.");
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		Mix_Init(MIX_INIT_OGG);
		TTF_Init();
	}
	switch (int code = init_engine()) {
	case 0:
		break;
	default:
		stacktrace(gl::mod.fail, std::format("Initialization failure {}", code));
		goto CLEANUP;
	}
	SDL_Event event;
	for (;;) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				goto CLEANUP;
			}
		}
	}
CLEANUP:
	stacktrace(gl::mod.core, "Shutting down.");
	{
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
	return 0;
}