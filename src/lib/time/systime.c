#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>

/* define only extern procedures required */
#pragma        extrn C_dow
#pragma        extrn C_doy
#pragma        extrn C_tz_dst
#pragma        extrn C_tzname

/* Kernel defines 8 bytes for RTC, we only need first 6 */
static   char _ts[8];

/*
 calculate the day of year from January 1
 */
int systime(struct tm *tp) {
  int  rtc;

  asm("clkrtc:     call  O_GETDEV              ; read rtc if one is present\n");
  asm("            glo   rf                    ; test if rtc is present\n");
  asm("            ani   10h\n");
  asm("            lbz   nortc\n\n");
  asm("            ldi   low C_ts              ; pointer to date buffer\n");
  asm("            plo   rf\n");
  asm("            ldi   high C_ts\n");
  asm("            phi   rf\n\n");
  asm("            call  O_GETTOD              ; read the RTC\n");
  asm("            load  ra, $0001             ; set RA to true\n");
  asm("            lbnz  clkdone               ; if successful we're done\n\n");

  asm("nortc:      ldi   low C_ts              ; pointer to date buffer\n");
  asm("            plo   rd\n");
  asm("            ldi   high C_ts\n");
  asm("            phi   rd\n\n");              
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
    
  /* Set tm fields from buffer */
  tp->tm_mon   = _ts[0] - 1;   /* C month offset is from 0 to 11, RTC is 1 to 12 */
  tp->tm_mday  = _ts[1];       /* month day 1 to 31 */
  tp->tm_year  = _ts[2] + 72;  /* C year offset is from 1900, RTC is from 1972 */
  tp->tm_hour  = _ts[3];       /* hours 0 to 23 */  
  tp->tm_min   = _ts[4];       /* minutes 0 to 59 */
  tp->tm_sec   = _ts[5];       /* seconds 0 to 59 */
  
  /* set tm fields calculatd from other fields */                             
  _dow(tp);     /* days since Sunday 0 to 6 */
  _doy(tp);     /* days since January 1,  0 to 365 */
  
  /* Set dst flag from timezone information */
  tp->tm_isdst = _tz_dst;      /* dst flag 1 for Yes, 0 for No, -1 for Unknown */
  
  return rtc;
}  
