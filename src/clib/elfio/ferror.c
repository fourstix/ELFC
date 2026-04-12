#define _ELFCLIB_
#include <stdio.h>

int ferror(FILE *f) {
	if (f == NULL) return 0;
	return (f->iom & _FERROR) != 0;
}
