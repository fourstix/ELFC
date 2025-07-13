#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr

int strspn(char *s, char *set) {
	int	i = 0;
	if (s) {
		while (*s && strchr(set, *s))
			s++, i++;
  }
	return i;
}
