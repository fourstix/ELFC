#define _ELFCLIB_
#include <stdio.h>

int feof(FILE *f) {
	//grw - NULL
	if (f == NULL) return 0;

	return (f->iom & _FEOF) != 0;
}
