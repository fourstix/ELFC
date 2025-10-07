#define _ELFCLIB_
#include <string.h>

 void *memcpy(void *d, void *s, size_t n) {
 if (d && s) {
	 asm("         gosub s_lget16  ; set the destination pointer");
	 asm("           dw 0          ; from argument stack");      
	 asm("         copy ra, rd     ; put destination pointer into rd");        
	 asm("         gosub s_lget16  ; set the source pointer");
	 asm("           dw 2          ; from argument stack");             
	 asm("         copy ra, rf     ; put source pointer into rf"); 
	 asm("         gosub s_lget16  ; get the counter");
	 asm("           dw 4          ; from argument stack");      
	       /* inline f_memcpy BIOS function  */
   asm("mcpy:    glo    ra       ; get low count byte");
   asm("         lbnz   mcpy1    ; jump if not zero");
   asm("         ghi    ra       ; get high count byte");
   asm("         lbz    mcdone   ; if zero copying is done");
   asm("mcpy1:   lda    rf       ; get byte from source");
   asm("         str    rd       ; store into destination");
   asm("         inc    rd       ; point to next destination position");
   asm("         dec    ra       ; decrement count");
   asm("         lbr    mcpy     ; and continue copy");
   asm("mcdone:  ");
 }
 return d;
}
/*
void *memcpy(void *d, void *s, int n) {
	char	*p;

	p = d;
	while (n--) *p++ = *(char *)s++;
	return d;
}
*/
