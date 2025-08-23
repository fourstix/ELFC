#define _ELFCLIB_
#include <stdlib.h>

/* define only extern procedures required */
#pragma           extrn Cmalloc

void *calloc(int count, int size) {
	void	*p, *m;
  int   n;
  
  n = count * size;

	if ((p = malloc(n)) == NULL)
		return NULL;
		
	/* save pointer to memory block for return */
	m = p;	
  while (n--) *(char *)p++ = 0;
  
	return m;
}
