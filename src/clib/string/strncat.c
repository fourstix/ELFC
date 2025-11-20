#define _ELFCLIB_
#include <string.h>

char *strncat(char *d, const char *a, size_t n) {
  if (d && a) {
    asm("         gosub s_lget16  ; set the destination pointer");
    asm("           dw 0          ; from argument stack");
    asm("         copy ra, rd     ; put destination pointer into rd");
    asm("         gosub s_lget16  ; set the source pointer");
    asm("           dw 2          ; from argument stack");
    asm("         copy ra, rf     ; put source pointer into rf");
		asm("         gosub s_lget16  ; set the count");
		asm("           dw 4          ; from argument stack");
		asm("         copy ra, rc     ; put counter into rc");
    asm("mend:    lda  rd         ; look for end of first string");
    asm("         lbnz mend       ; loop until terminator found");
    asm("         dec  rd         ; move to terminator and copy second string");
		asm("loop:    lda  rf         ; get byte from source string");
		asm("         str  rd         ; store into destination");
		asm("         inc  rd         ; move to next position");
		asm("         lbz  done       ; exit if terminator copied");
		asm("         dec  rc         ; decrement characters to concatenate");
		asm("				  glo  rc         ; see if done");
		asm("					lbnz loop       ; loop if not done");
		asm("					ghi  rc         ; check high byte");
		asm(" 				lbnz loop       ; loop if not done");
		asm("done:    adi  0          ; clear DF");
   }
	 return d;
 }

/*
char *strncat(char *d, char *a, int n) {
	char	*p;

	if (d && a) {
		for (p = d; *p; p++)
			;
		for (; n && *a; n--)
			*p++ = *a++;
		*p = 0;
  }
	return d;
}
*/
