#define SDL_MAIN_HANDLED
#include "internal/include.hpp"
#include "core/include.hpp"
#include "modloader/include.hpp"
#include "maploader/include.hpp"
#include "client/include.hpp"
int preliminary_check(void) {
	switch (int code = init_engine()) {
	case 0: break;
	case 1: stacktrace(gl::mod.error, "Unable to start: the program requires OpenGL 4.0+ to run.");
	default:
		stacktrace(gl::mod.fail, std::format("Initialization failure {}", code));
		return code;
	}
	return 0;
}
int main(int argc, char** argv) {
	(void)argc; (void)argv;
	stacktrace(gl::mod.core, "Initialization started.");
	cleanup([] {
		stacktrace(gl::mod.core, "Shutting down.");
		shutdown_engine();
	});
	try {
		if (int check_result = preliminary_check(); check_result != 0) return check_result;
		node::window main_window = node::make_window("default", 1000u, 600u);
		stacktrace(gl::mod.core, "Game started!");
		for (SDL_Event event; SDL_WaitEvent(&event), event.type != SDL_QUIT; main_window.update()) {
			switch (event.type) {
			case SDL_KEYUP:
				return 0;
			}
		}
		throw std::system_error(std::make_error_code(std::errc::interrupted));
	} catch (std::system_error& e) {
		return e.code().value();
	} catch (...) {
		stacktrace(gl::mod.fail, std::format("An unhandled exception occured."));
	}
	return 127001;
}