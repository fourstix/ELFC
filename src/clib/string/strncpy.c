#define _ELFCLIB_
#include <string.h>
/*
 *	NMH's Simple C Compiler, 2011,2012,2014
 *	strncpy()
 */

char *strncpy(char *d, const char *s, size_t n) {
	char	*p;

	for (p = d; n && *s; n--)
		*p++ = *s++;
	while (n--) *p++ = 0;
	return d;
}
