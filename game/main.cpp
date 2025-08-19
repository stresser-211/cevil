#define SDL_MAIN_HANDLED
#include "internal/include"
#include "core/include"
#include "modloader/include"
#include "maploader/include"
#include "client/include"
#include <argparse.hpp>
int preliminary_check(void) { /* messy, i'l refactor it later */
	switch (int code = init_engine()) {
	case 0: break;
	case 1: stacktrace(MODULE::SYSTEM, ERROR::OUTDATED_OPENGL);
	default:
		stacktrace(MODULE::SYSTEM, ERROR::INIT_FAILURE, std::to_string(code));
		return code;
	}
	init_client();
	init_modloader();
	init_maploader();
	return 0;
}
int main(int argc, char** argv) {
	//(void)argc; (void)argv; //--log:verbose
	stacktrace(MODULE::SYSTEM, ERROR::INFO_STARTUP);
	cleanup([] {
		stacktrace(MODULE::SYSTEM, ERROR::INFO_SHUTDOWN);
		shutdown_engine();
	});
	try {
		if (int check_result = preliminary_check(); check_result != 0) return check_result;
		get_config();
		node::window main_window = node::make_window("default", 1000u, 600u);
		stacktrace(MODULE::GAME, ERROR::INFO_GAME_STARTED);
		for (SDL_Event event; SDL_WaitEvent(&event), event.type != SDL_QUIT; main_window.update()) {
			switch (event.type) {
			case SDL_KEYUP:
				return 0;
			}
		}
	} catch (std::exception e) {
		fprintf(fopen("../ae.txt", "w"), e.what());
	} catch (...) {
		stacktrace(MODULE::SYSTEM, ERROR::UNHANDLED_EXCEPTION);
	}
	return 127001;
}