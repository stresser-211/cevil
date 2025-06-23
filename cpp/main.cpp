#include "utility.hpp"
#include "nodes.hpp"

int engine_init(void) {
	if (get_config() < 0) {
		stacktrace(_module.error, "---Couldn't get config file---");
		return 1;
	}
	if (Mix_OpenAudio(44100, AUDIO_S16, 2, 2048) < 0) {
		stacktrace(_module.error, "---Couldn't open audio device---");
		return 2;
	}
}

int main(int argc, char** argv) {
	(void)argc; (void)argv;
	stacktrace(gl::mod.core, "---Initialisation---");
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		Mix_Init(MIX_INIT_OGG);
		TTF_Init();
	}
	int code = engine_init();
	if (code > 0) {
		stacktrace(gl::mod.error, std::format("---Engine initialisation failure; error code: {}---", code).c_str());
		goto CLEANUP; /* Everybody going apeshit in 3, 2, 1... */
	}
	{
		SDL_Event event;
		for (;;) {
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_QUIT:
					goto CLEANUP;
				}
			}
		}
	}
CLEANUP:
	stacktrace(gl::mod.core, "---Shutting down---");
	{
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
	return 0;
}