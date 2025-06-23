#ifndef NODES_H
#define NODES_H
#include "__internal/preprocessor.hpp"
#include "__internal/objects.hpp"
#include "__internal/global.hpp"
namespace node {
	class cell {
		objects::texture txtr;
		int64_t vertex[6];
		int64_t x;
		int64_t y;
	public:
		cell(void) = delete;
		explicit cell(auto tmp) {
		}
	};
}
#endif /* NODES_H */