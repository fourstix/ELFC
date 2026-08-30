#define _ELFCLIB_
#include <stdlib.h>

/*
 * Get system time values from OS
 * Return 1, if RTC is present
 *        0, if no RTC found
 */
int _systime(char *ts) {
  int  rtc;

  asm("clkrtc:     call  O_GETDEV              ; read rtc if one is present\n");
  asm("            glo   rf                    ; test if rtc is present\n");
  asm("            ani   10h\n");
  asm("            lbz   nortc\n\n");
  asm("            gosub s_lget16              ; get the destination pointer");
  asm("               dw 0                     ; from argument stack");
  asm("            copy ra, rf                 ; put pointer to date buffer into rf");

  asm("            call  O_GETTOD              ; read the RTC\n");
  asm("            load  ra, $0001             ; set RA to true\n");
  asm("            lbnf  clkdone               ; if successful we're done\n\n");

  asm("nortc:      gosub s_lget16              ; get the destination pointer");
  asm("               dw 0                     ; from argument stack");
  asm("            copy ra, rd                 ; put pointer to date buffer into rd");

  asm("            ldi   low K_MONTH           ; date variable but start from end\n");
  asm("            plo   rf\n");
  asm("            ldi   high K_MONTH\n");
  asm("            phi   rf\n\n");

  asm("            ldi   6			               ; 6 bytes to copy\n");
  asm("            plo   rc\n");
  asm("cpylp:      lda   rf\n");
  asm("            str   rd\n");
  asm("            inc   rd\n");
  asm("            dec   rc\n");
  asm("            lbnz  cpylp\n");
  asm("            load  ra, $0000             ; set RA to false\n");
  asm("clkdone:    gosub s_lset16              ; store RA in rtc flag\n");
  asm("              dw   -2\n");

  return rtc;
}
