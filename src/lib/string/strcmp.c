int strcmp(char *s1, char *s2) {
  int  dif;
  dif = s1 - s2; /* in case either string is null */
  
  if (s1 && s2) {
    asm("         call lget16     ; set the first string pointer");
    asm("           dw 0          ; from argument stack");      
    asm("         copy ra, rf     ; put s1 pointer into rf");        
    asm("         call lget16     ; set the second string pointer");
    asm("           dw 2          ; from argument stack");             
    asm("         copy ra, rd     ; put s2 pointer into rd");
    asm("cmp:     lda     rd      ; get next byte in s2");
	  asm("         str     r2	    ; store in M(X)");
    asm("         lda     rf      ; get byte from first string");
    asm("         lbz     cmpe    ; check for end of second string");
    asm("         sm              ; subtract s2 byte from it");
    asm("         lbz     cmp     ; so far a match, keep looking");
    asm("         lbr     done    ; if different, we're done");
    asm("cmpe:    ldx             ; check s2 M(X);");
    asm("         lbz     done    ; if also terminator, s1 == s2");
    asm("         sdi  0          ; negate D, because s1 < s2");  
    asm("done:    plo  ra         ; put D value in ra");
    asm("         shl             ; shift msb into DF to check sign bit");
    asm("         ldi  0          ; put zero D for positive");
    asm("         lsnf            ; skip two bytes if positive");
    asm("         ldi  $FF        ; signed byte for negative");
    asm("         phi  ra         ; put sign extension into ra");
    asm("         call lset16     ; set the return value");
    asm("           dw -2         ; in the argument stack");
  }             
  return dif;
}
