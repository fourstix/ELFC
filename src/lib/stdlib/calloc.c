#define _ELFCLIB_
#include <stdlib.h>

/* define only extern procedures required */
#pragma           extrn Cmalloc

void *calloc(int count, int size) {
	void	*p;
  int   n;
  
  n = count * size;

	if ((p = malloc(n)) == NULL)
		return NULL;

  while (n--) *(char *)p++ = 0;
  
	return p;

}
