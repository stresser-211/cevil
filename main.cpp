#include "utility.hpp"
#include "basic_objects.hpp"
int main(int argc, char** argv) {
	{
		SDL_Init(SDL_INIT_EVERYTHING);
		IMG_Init(IMG_INIT_PNG);
	}
	if (!get_config()) {
		goto CLEANUP; /* Everyone going apeshit in 3, 2, 1... */
	}
	{
		SDL_Event event;
		window main_window("Cevil");
		SDL_RenderPresent(main_window.get_renderer());
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
		IMG_Quit();
		SDL_Quit();
	}
	return 0;
}
