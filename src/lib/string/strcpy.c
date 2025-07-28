
char *strcpy(char *d, char *s) {
  if (d && s) {
    asm("         call lget16     ; set the destination pointer");
    asm("           dw 0          ; from argument stack");      
    asm("         copy ra, rd     ; put destination pointer into rd");        
    asm("         call lget16     ; set the source pointer");
    asm("           dw 2          ; from argument stack");             
    asm("         copy ra, rf     ; put source pointer into rf"); 
    asm("         call f_strcpy   ; call bios strcpy function");
  }
  return d;
}
