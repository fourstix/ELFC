
int memcmp(void *p1, void *p2, int n) {
  int  dif;
	/* return value in case either string is null */
  dif = p1 - p2; 
   
  if (p1 && p2) {
    asm("         call lget16     ; set the first string pointer");
    asm("           dw 0          ; from argument stack");      
    asm("         copy ra, rf     ; put destination pointer into rd");        
    asm("         call lget16     ; set the second string pointer");
    asm("           dw 2          ; from argument stack");             
    asm("         copy ra, rd     ; put source pointer into rf"); 
		asm("         call lget16     ; set the counter");
    asm("           dw 4          ; from argument stack");      
    asm("         copy ra, rc     ; put counter into rc");        
		asm("loop:    lda  rf         ; get byte from first string");
		asm("         str  r2         ; store for compare");
		asm("         lda  rd         ; get byte from second string");
		asm("         sm              ; compare");
		asm("         lbnz bad        ; jump if no match");
		asm("         dec  rc         ; decrement characters to compare");
		asm("         glo  rc         ; see if done");
		asm("         lbnz loop       ; loop if not done");
		asm("         ghi  rc         ; check high byte");
		asm("         lbnz loop       ; loop if not done");
		asm("         ldi  0          ; put zero for match");
		asm("         phi  ra         ; set hi byte for return");
		asm("         plo  ra         ; set lo byte for return");
		asm("         lbr  done       ; return with value in ra");
    asm("bad:     plo  ra         ; put D value in ra");
    asm("         shl             ; shift msb into DF to check sign bit");
    asm("         ldi  0          ; put zero D for positive");
    asm("         lsnf            ; skip two bytes if positive");
    asm("         ldi  $FF        ; signed byte for negative");
    asm("         phi  ra         ; put sign extension into ra");
    asm("done:    call lset16     ; set the return value");
    asm("           dw -2         ; in the argument stack");
		asm("         adi      0      ; clear DF after arithmetic");
  }             
  return dif;	 
}

/*
int memcmp(void *p1, void *p2, int n) {
	while (n-- && *(char *)p1++ == *(char *)p2++)
		;
	return *(char *)--p1 - *(char *)--p2;
}
*/
