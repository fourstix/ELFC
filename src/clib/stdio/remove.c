#define _ELFCLIB_
#include <stdlib.h>

#pragma             extrn Cunlink

int remove(char *path) {
	return unlink(path);
}
