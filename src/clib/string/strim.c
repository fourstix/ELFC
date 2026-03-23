#define _ELFCLIB_
#include <string.h>
#include <ctype.h>

#pragma           extrn Cisspace
#pragma           extrn Cmemmove
#pragma           extrn Cstrlen

char *strim(char *str) {
  char *start, *end;

  /* Find first non-whitespace */
  for (start = str; *start; start++) {
      if (!isspace((unsigned char)start[0]))
          break;
  }

  /* Find start of last all-whitespace */
  for (end = start + strlen(start); end > start + 1; end--) {
      if (!isspace((unsigned char)end[-1]))
          break;
  }

  *end = 0; /* Truncate last whitespace */

  /* Shift from "start" to the beginning of the string */
  if (start > str) {
    memmove(str, start, (end - start) + 1);
  }

  return str;
}
