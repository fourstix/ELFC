
char *strcpy(char *d, char *s) {
  if (d && s) {
    asm("         gosub s_lget16  ; set the destination pointer");
    asm("           dw 0          ; from argument stack");      
    asm("         copy ra, rd     ; put destination pointer into rd");        
    asm("         gosub s_lget16  ; set the source pointer");
    asm("           dw 2          ; from argument stack");             
    asm("         copy ra, rf     ; put source pointer into rf"); 
    /* inline f_strcpy BIOS function  */
    asm("scopy:   lda    rf       ; get a character from source");
    asm("         str    rd       ; and store into destination");
    asm("         lbz    cpydone  ; finish if we copied the null");
    asm("         inc    rd       ; increment destination pointer");
    asm("         lbr    scopy    ; continue looping until done");
    asm("cpydone:  ");         
  }
  return d;
}
