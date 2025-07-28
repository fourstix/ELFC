#define _ELFCLIB_
#include <stdlib.h>
#include <string.h>

#pragma           extrn Cmalloc
#pragma           extrn Cstrlen
#pragma           extrn Cstrcpy

char *strdup(char *s) {
	char	*p;
	p = NULL;

	if (s) {
		if ((p = malloc(strlen(s)+1)) == NULL)
			return NULL;
		strcpy(p, s);
  }
	return p;
}
