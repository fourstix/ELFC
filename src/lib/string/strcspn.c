#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr

size_t strcspn(char *s, char *set) {
	int	i = 0;

	while (*s && !strchr(set, *s))
		s++, i++;
	return i;
}
