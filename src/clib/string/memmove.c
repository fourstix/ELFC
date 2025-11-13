#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cmemcpy

void *memmove(void *d, const void *s, size_t n) {
	char	*p;

	if (d < s) return memcpy(d, s, n);
	p = d + n;
	s += n;
	while (n--) *--p = *(char *)--s;
	return d;
}
