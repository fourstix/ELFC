#define _ELFCLIB_

#include <stdlib.h>
#include <time.h>


#pragma              extrn Csystime
#pragma              extrn C_tz_min
#pragma              extrn C_tz_hr
#pragma              extrn C_tz_dst
#pragma              extrn C_dow
#pragma              extrn C_doy

static int _nmday[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/*
 Calculate the Universal Co-ordinated Time 
 */
int utctime(struct tm *tp) {
  int leap;     /* leap year flag */
  int nmdays;   /* number of days in current month */
  int rtc;      /* flag to indicate RTC used */
  
  /* get the system time */
  rtc = systime(tp);

  /* set leap year flag */  
  leap = (tp->tm_year % 4 == 0 && (tp->tm_year % 100 != 0 || tp->tm_year % 400 == 0));

  
  /* adjust minutes for time zone offset */
  tp->tm_min -= _tz_min;
  
  if (tp->tm_min < 0) {
    tp->tm_min += 60;
    tp->tm_hour--;
  } else if (tp->tm_min >= 60) {
    tp->tm_min -= 60;
    tp->tm_hour++;
  }

  
  /* adjust hours for time zone offset */
  tp->tm_hour -= _tz_hr;
  
  /* if dst in effect, remove hour */
  if (tp->tm_isdst == 1) {
      tp->tm_hour--;
  }
  
  
  if (tp->tm_hour < 0) {
    tp->tm_hour += 24;
    tp->tm_mday++;
  } else if (tp->tm_hour >= 24) {
    tp->tm_hour -= 24;
    tp->tm_mday--;
  }
  
  /* mday is from 1 to 31, 30, 29 or 28 */
  if (tp->tm_mday < 0) {
    tp->tm_mon--;
    /* Set day to last of month */
    tp->tm_mday += _nmday[tp->tm_mon];
    /* If February adjust last day for leap day */
    if (tp->tm_mon == 2) {
      tp->tm_mday += leap;
    }
  } else {
    /* Get days in current month */
    nmdays = _nmday[tp->tm_mon];
    /* If February adjust end of month day for leap day */
    if (tp->tm_mon == 2) {
      nmdays += leap;
    }
    /* Are we past the end of the month? */
    if (tp->tm_mday > nmdays) {
      /* if so adjust month */
      tp->tm_mon++;
      /* set to first day of next month */
      tp->tm_mday = 1;
    }
  }
 
 /* now adjust months, if it's New Year's Eve */
 if (tp->tm_mon < 0) {
   /* December of last year */
   tp->tm_mon = 11;
   tp->tm_year--;
 } else if (tp->tm_mon > 11) {
   /* January of next year */
   tp->tm_mon = 0;
   tp->tm_year++;
 }

/* Now set the related fields for day of week and day of year */
_dow(tp);
_doy(tp);

/* Daylight Savings Time is never in effect for UTC */
tp->tm_isdst = 0; 

return rtc;
}
