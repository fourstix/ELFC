#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr


char *strpbrk(char *s, char *set) {
	while (*s && !strchr(set, *s))
		s++;
	return *s? s: NULL;
}
