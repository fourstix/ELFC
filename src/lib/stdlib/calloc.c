#define _ELFCLIB_
#include <stdlib.h>

/* define only extern procedures required */
#pragma           extrn Cmalloc

void *calloc(size_t count, size_t size) {
	void	*p, *m;
  size_t   n;
  
  n = count * size;

	if ((p = malloc(n)) == NULL)
		return NULL;
		
	/* save pointer to memory block for return */
	m = p;	
  while (n--) *(char *)p++ = 0;
  
	return m;
}
