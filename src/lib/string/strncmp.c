
 int strncmp(char *s1, char *s2, int n) {
	 int  dif;
	 /* return value in case either string is null */
   dif = s1 - s2; 
   
   if (s1 && s2) {
     asm("         gosub s_lget16  ; set the first string pointer");
     asm("           dw 0          ; from argument stack");      
     asm("         copy ra, rf     ; put s1 pointer into rf");        
     asm("         gosub s_lget16  ; set the second string pointer");
     asm("           dw 2          ; from argument stack");             
     asm("         copy ra, rd     ; put s2 pointer into rd"); 
		 asm("         gosub s_lget16  ; set the counter");
     asm("           dw 4          ; from argument stack");      
     asm("         copy ra, rc     ; put counter into rc");        
		 asm("loop:    lda  rf         ; get byte from first string");
		 asm("         str  r2         ; store for compare");
		 asm("         lda  rd         ; get byte from second string");
     asm("         lbz  ends2      ; if end of s2, check s1");

		 asm("         sd              ; compare M(X) - D => s1 - s2");
		 asm("         lbnz bad        ; jump if no match");
     asm("         ldx             ; check M(X) to see if we hit the terminator");
     asm("         lbz  match      ; if we hit the terminator, strings match");     
		 asm("         dec  rc         ; decrement characters to compare");
		 asm("         glo  rc         ; see if done");
		 asm("         lbnz loop       ; loop if not done");
		 asm("         ghi  rc         ; check high byte");
		 asm("         lbnz loop       ; loop if not done");
		 asm("match:   ldi  0          ; put zero for match");
		 asm("         phi  ra         ; set hi byte for return");
		 asm("         plo  ra         ; set lo byte for return");
		 asm("         lbr  done       ; return with value in ra");
     asm("ends2:   ldx             ; check M(X) to see if we hit the terminator");
     asm("         lbz  match      ; if terminator, strings match, else bad");
     asm("bad:     plo  ra         ; put D value in ra");
     asm("         shl             ; shift msb into DF to check sign bit");
     asm("         ldi  0          ; put zero D for positive");
     asm("         lsnf            ; skip two bytes if positive");
     asm("         ldi  $FF        ; signed byte for negative");
     asm("         phi  ra         ; put sign extension into ra");
     asm("done:    gosub s_lset16  ; set the return value");
     asm("           dw -2         ; in the argument stack");
		 asm("         adi      0      ; clear DF after arithmetic");
   }             
   return dif;	 
 }

/*
int strncmp(char *s1, char *s2, int n) {
	while (n && *s1 && *s1 == *s2)
		s1++, s2++, n--;
	return n? *s1 - *s2: 0;
}
*/
