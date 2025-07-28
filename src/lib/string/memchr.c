#define _ELFCLIB_
#include <string.h>

void *memchr(void *p, int c, int n) {
	char *q;
	q = NULL;
	
	if (p) {
		asm("         call lget16     ; set the memory pointer");
		asm("           dw 0          ; from argument stack");      
		asm("         copy ra, rf     ; put memory pointer into rf");        
		asm("         call lget16     ; set the counter");
		asm("           dw 4          ; from argument stack");      
		asm("         copy ra, rc     ; put counter into rc");
		asm("         call lget16     ; set the search character");
		asm("           dw 2          ; from argument stack");             
		asm("         glo  ra     		; put search character into M(X)");
		asm("         str  r2         ; for comparisons");	 		
		asm("loop:    glo  rc         ; get low count byte");
		asm("         lbnz memchr     ; jump if not zero");
		asm("         ghi  rc         ; get high count byte");
		asm("         lbz  notfnd     ; quit if zero");
		asm("memchr:  lda  rf         ; get character from memory");
		asm("         sm              ; compare to requested character");
		asm("         lbz  match      ; quit if we found match");
		asm("         dec  rc         ; decrement count");
		asm("         lbr  loop       ; continue searching memory");
		asm("match:   dec  rf         ; move RF back to found character");
		asm("         copy  rf, ra    ; copy memory pointer to found character");
		asm("         call lset16     ; set the return value");
		asm("           dw -2         ; in the local variable on the stack");   
		asm("notfnd:  adi  0          ; clear DF for return"); 				 
	}
	return q;
}

/*
void *memchr(void *p, int c, int n) {
	while (n--) {
		if (*(char *)p == c) return p;
		p++;
	}
	return NULL;
}
*/
