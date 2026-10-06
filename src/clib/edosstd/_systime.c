#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

/*
 * Get system time values from OS
 * Return 1, if RTC is present
 *        0, if no RTC found
 */
int _systime(char *ts) {
  int  rtc;

  _KSAVE
  asm("            call  K_GETDEV              ; get the devices present\n");
  _KRESTORE
  asm("            glo   rf                    ; test if rtc is present\n");
  asm("            ani   10h\n");
  asm("            lbz   nortc\n\n");
  asm("            gosub s_lget16              ; get the destination pointer");
  asm("               dw 0                     ; from argument stack");
  asm("            copy ra, rf                 ; put pointer to date buffer into rf");
  _KSAVE
  asm("            call  K_GETTOD              ; read the RTC\n");
  _KRESTORE
  asm("            load  ra, $0001             ; set RA to true\n");
  asm("            lbnf  clkdone               ; if successful we're done\n\n");
  asm("nortc:      load  ra, $0000             ; set RA to false\n");
  asm("clkdone:    gosub s_lset16              ; store RA in rtc flag\n");
  asm("              dw   -2\n");

  /* ELF-DOS keeps no date of its own, so without an RTC */
  /* use its default of midnight on January 1, 2000 */
  if (!rtc) {
    ts[0] = 1;     /* month */
    ts[1] = 1;     /* day */
    ts[2] = 28;    /* years since 1972 */
    ts[3] = 0;     /* hour */
    ts[4] = 0;     /* minute */
    ts[5] = 0;     /* second */
  }

  return rtc;
}
