#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr

char *strrchr(char *s, int c) {
	char	*p;

	p = NULL;
	if (s) {
	while (*s)
		if (*s++ == c)
			p = s-1;
	}		
	return p;
}
