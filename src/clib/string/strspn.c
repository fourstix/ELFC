#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr

size_t strspn(const char *s, const char *set) {
	int	i = 0;
	if (s) {
		while (*s && strchr(set, *s))
			s++, i++;
  }
	return i;
}
