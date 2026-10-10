#define _ELFCLIB_
#include <stdlib.h>

#pragma             extrn Cunlink

int remove(const char *path) {
	return unlink(path);
}
