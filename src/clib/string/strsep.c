#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrcspn

char *strsep(char **str, const char *sep) {
  char *s = *str, *end;

  if (!s) return NULL;

	end = s + strcspn(s, sep);
	if (*end) *end++ = 0;
	else end = NULL;
	*str = end;
	return s;
}
