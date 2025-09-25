#define _ELFCLIB_
#include <stdlib.h>
#include <string.h>

/* define only extern procedures required */
#pragma           extrn Cmalloc
#pragma           extrn Cfree
#pragma           extrn Cmemcpy
#pragma .link .library string.lib


void *realloc(void* p, int size) {
	void	*new;
  int   osize;
	int   n;
  
	/* null is invalid, so give up */
	if (p == NULL) return NULL;
	
	/* get the memory block size directly from the heap */
	asm("         gosub s_lget16  ; get the old pointer value");
	asm("           dw 0          ; from argument stack");             
	asm("         copy ra, rf     ; put pointer into rf"); 
	asm("         dec rf          ; walk back 2 bytes before memory block");
	asm("         dec rf          ; to get the memory block size");
	asm("         lda rf          ; get the size hi byte (MSB)");
	asm("         phi ra          ; set high byte to store ");
	asm("         lda rf          ; get the size lo byte (LSB)");
	asm("         plo ra          ; set lo byte to store ");
	asm("         gosub s_lset16  ; set the old size value");
	asm("           dw -4         ; in the local argument stack");  

	if ((new = malloc(size)) == NULL)
		return NULL;
	
	/* set the number of bytes to copy */	
  n = (size > osize) ? osize : size;
	
	/* copy bytes from old into new */
	memcpy(new, p, n);
	
	/* free the old memory */
  free(p);
  
	/* return pointer to new memory */
	return new;
}
