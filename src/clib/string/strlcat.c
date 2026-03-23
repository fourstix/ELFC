#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrlen
#pragma           extrn Cstrnlen
#pragma           extrn Cstrlcpy

size_t strlcat(char *d, const char *s, size_t n) {
  size_t len = strnlen(d, n);
  if (len == n) return len + strlen(s);
  return len + strlcpy(d+len, s, n-len);
 }
