#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cmemcpy
 
void *memmove(void *d, void *s, int n) {
	char	*p;

	if (d < s) return memcpy(d, s, n);
	p = d + n;
	s += n;
	while (n--) *--p = *(char *)--s;
	return d;
}
