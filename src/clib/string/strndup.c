#define _ELFCLIB_
#include <stdlib.h>
#include <string.h>

#pragma           extrn Cmalloc
#pragma           extrn Cstrnlen
#pragma           extrn Cmemcpy

char *strndup(const char *s, size_t n) {
	size_t len   = strnlen(s, n);
	char *d = malloc(len+1);
	if (!d) return NULL;
	memcpy(d, s, len);
	d[len] = 0;
	return d;
}
