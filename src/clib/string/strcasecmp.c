#define _ELFCLIB_
#include <string.h>
#include <ctype.h>

#pragma           extrn Ctolower

int strcasecmp(const char *s1, const char *s2) {
  const unsigned char *p1=(void *)s1, *p2=(void *)s2;
	for (; *p1 && *p2 && (*p1 == *p2 || tolower(*p1) == tolower(*p2)); p1++, p2++);
	return tolower(*p1) - tolower(*p2);
}
