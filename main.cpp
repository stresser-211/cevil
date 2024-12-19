#include "utility.hpp"
#include "nodes.hpp"

int main(int argc, char** argv) {
	stacktrace(_module.core, "---Initialisation---");
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
		Mix_Init(MIX_INIT_OGG);
		TTF_Init();
	}
	if (!get_config()) {
		goto CLEANUP; /* Everyone going apeshit in 3, 2, 1... */
	}
	{
		SDL_Event event;
		window::native main_window("Cevil");
		main_window.show();
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
	stacktrace(_module.core, "---Shutting down---");
	{
		TTF_Quit();
		Mix_Quit();
		IMG_Quit();
		SDL_Quit();
	}
	return 0;
}