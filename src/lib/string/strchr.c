#define _ELFCLIB_
#include <string.h>

char *strchr(char *s, int c) {
  char *p;
  p = NULL;
  if (s) {
    asm("         call lget16     ; set the source pointer");
    asm("           dw 0          ; from argument stack");             
    asm("         copy ra, rf     ; put source pointer into rf");
    asm("         call lget16     ; set the search character");
    asm("           dw 2          ; from argument stack");             
    asm("         glo  ra         ; put character value into M(x)");  
    asm("         str  r2         ; for comparisons");
    asm("loop:    lda  rf         ; get byte from string");
    asm("         lbz  notfnd     ; jump if end of string");
    asm("         sm              ; compare to requested character");
    asm("         lbnz loop       ; loop until found or terminator");
    asm("         dec  rf         ; move RF back to found character");
    asm("         copy  rf, ra    ; copy pointer to found character");
    asm("         call lset16     ; set the return value");
    asm("           dw -2         ; in the argument stack");   
    asm("notfnd:  adi  0          ; clear DF after arithmetic");
  }
  return p;
  
  
  /*
	while (*s && *s != c)
		s++;
	return *s || !c ? s: NULL;
  */
}
