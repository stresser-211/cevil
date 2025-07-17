#define EXPORT
#include "self.hpp"
constexpr Int16T port = 12701;
extern "C" {
	int API init_client(void) {
		return 0;
	}
}