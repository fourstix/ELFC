char *strcat(char *d, char *a) {
  if (d && a) {
    asm("         call lget16     ; set the destination pointer");
    asm("           dw 0          ; from argument stack");      
    asm("         copy ra, rd     ; put destination pointer into rd");        
    asm("         call lget16     ; set the source pointer");
    asm("           dw 2          ; from argument stack");             
    asm("         copy ra, rf     ; put source pointer into rf"); 
    asm("mend:    lda  rd         ; look for end of first string");
    asm("         lbnz mend       ; loop until terminator found");
    asm("         dec  rd         ; move to terminator and copy second string");
    asm("         call f_strcpy   ; call bios strcpy function");
  }
  return d;
}
