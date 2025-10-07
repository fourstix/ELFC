#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrchr
#pragma           extrn Cstrncmp
#pragma           extrn Cstrlen

char *strstr(char *s1, char *s2) {
  int len2;
  char *p;

  len2 = strlen(s2);

  for (p = (char*)s1; p != NULL; p = strchr(p, *s2)) {
    if (!strncmp(p, s2, len2)) {
      break;
    }
    p++;
  }

  return p;
}
