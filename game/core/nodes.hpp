#ifndef CORE_NODES_H
#define CORE_NODES_H
#include "../internal/include.hpp"
#include "sdl.hpp"
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