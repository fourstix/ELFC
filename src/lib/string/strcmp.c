int strcmp(char *s1, char *s2) {
  int  dif;
  dif = s1 - s2; /* in case either string is null */
  
  if (s1 && s2) {
    asm("         call lget16     ; set the first string pointer");
    asm("           dw 0          ; from argument stack");      
    asm("         copy ra, rf     ; put destination pointer into rd");        
    asm("         call lget16     ; set the second string pointer");
    asm("           dw 2          ; from argument stack");             
    asm("         copy ra, rd     ; put source pointer into rf"); 
    asm("         call f_strcmp   ; call bios strcpmp function");
    asm("         plo  ra         ; put D value in ra");
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
