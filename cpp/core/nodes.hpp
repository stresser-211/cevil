#ifndef CORE_NODES_H
#define CORE_NODES_H
#include "sdl.hpp"
#include "../internal/preprocessor.hpp"
#include "../internal/serialcocksucker.hpp"
#include "fundamentals.hpp"
namespace node {
	class cell {
		basic::texture txtr;
		Int64T vertex[6];
		Int64T x, y;
	public:
		cell(void) = delete;
		explicit cell(auto tmp) {
		}
	};
}
#endif /* CORE_NODES_H */