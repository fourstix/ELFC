#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr

size_t strcspn(const char *s, const char *set) {
	int	i = 0;

	while (*s && !strchr(set, *s))
		s++, i++;
	return i;
}
