char *strcat(char *d, const char *a) {
  if (d && a) {
    asm("         gosub s_lget16  ; set the destination pointer");
    asm("           dw 0          ; from argument stack");
    asm("         copy ra, rd     ; put destination pointer into rd");
    asm("         gosub s_lget16  ; set the source pointer");
    asm("           dw 2          ; from argument stack");
    asm("         copy ra, rf     ; put source pointer into rf");
    asm("mend:    lda  rd         ; look for end of first string");
    asm("         lbnz mend       ; loop until terminator found");
    asm("         dec  rd         ; move to terminator and copy second string");
    /* inline f_strcpy BIOS function  */
    asm("scat:    lda    rf       ; copy the second string");
    asm("         str    rd       ; into the destination");
    asm("         lbz    sctdone  ; finish if copied null");
    asm("         inc    rd       ; increment destination pointer");
    asm("         lbr    scat     ; continue looping until done");
    asm("sctdone:  ");
  }
  return d;
}
