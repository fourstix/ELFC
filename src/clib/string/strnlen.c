#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cmemchr

size_t strnlen(const char *s, size_t n) {
	const char *p = memchr(s, 0, n);
  return p ? p-s : n;
}
