#define _ELFCLIB_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* define only extern procedures required */
#pragma extrn Csprintf
#pragma extrn C_tzname
#pragma extrn C_tz_offset
#pragma extrn Cdivi32
#pragma extrn Ci32_from_int
#pragma extrn Cint_from_i32

#define SECS_PER_MIN 60
#define SECS_PER_HOUR 3600

static char *_add(char *str, char *pt, char *ptlim)
{
  while (pt < ptlim && (*pt = *str++) != '\0') ++pt;
  return pt;
}

static char *_conv(int n, char *format, char *pt, char *ptlim)
{
  static char buf[32];

  sprintf(buf, format, n);
  return _add(buf, pt, ptlim);
}

static char *_fmt(char *format, struct tm *t, char *pt, char *ptlim)
{
  static char *_days[7] = {"Sunday",   "Monday", "Tuesday", "Wednesday",
                           "Thursday", "Friday", "Saturday"};
  static char *_months[12] = {"January",   "February", "March",    "April",
                              "May",       "June",     "July",     "August",
                              "September", "October",  "November", "December"};
  static char *_days_ab[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  static char *_months_ab[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  int tz_hr;
  int32_t tz_sec;

  for (; *format; ++format) {
    if (*format == '%') {
      switch (*++format) {
        case '\0':
          --format;
          break;

        case 'A':
          pt =
              _add((t->tm_wday < 0 || t->tm_wday > 6) ? "?" : _days[t->tm_wday],
                   pt, ptlim);
          continue;

        case 'a':
          pt = _add(
              (t->tm_wday < 0 || t->tm_wday > 6) ? "?" : _days_ab[t->tm_wday],
              pt, ptlim);
          continue;

        case 'B':
          pt =
              _add((t->tm_mon < 0 || t->tm_mon > 11) ? "?" : _months[t->tm_mon],
                   pt, ptlim);
          continue;

        case 'b':
     /* case 'h': */
          pt = _add(
              (t->tm_mon < 0 || t->tm_mon > 11) ? "?" : _months_ab[t->tm_mon],
              pt, ptlim);
          continue;
/*
        case 'C':
          pt = _conv((t->tm_year + 1900) / 100, "%02d", pt, ptlim);
          continue;
*/
        case 'c':
          pt = _fmt("%a %b %e %H:%M:%S %Y", t, pt, ptlim);
          continue;
/*
        case 'D':
          pt = _fmt("%m/%d/%y", t, pt, ptlim);
          continue;
*/
        case 'd':
          pt = _conv(t->tm_mday, "%02d", pt, ptlim);
          continue;
/*
        case 'e':
          pt = _conv(t->tm_mday, "%2d", pt, ptlim);
          continue;
*/

        case 'F':
          pt = _fmt("%Y-%m-%d", t, pt, ptlim);
          continue;

        case 'H':
          pt = _conv(t->tm_hour, "%02d", pt, ptlim);
          continue;

        case 'I':
          pt = _conv((t->tm_hour % 12) ? (t->tm_hour % 12) : 12, "%02d", pt,
                     ptlim);
          continue;

        case 'j':
          pt = _conv(t->tm_yday + 1, "%03d", pt, ptlim);
          continue;
/*
        case 'k':
          pt = _conv(t->tm_hour, "%2d", pt, ptlim);
          continue;

        case 'l':
          pt = _conv((t->tm_hour % 12) ? (t->tm_hour % 12) : 12,
              "%2d", pt, ptlim); continue;
*/
        case 'M':
          pt = _conv(t->tm_min, "%02d", pt, ptlim);
          continue;

        case 'm':
          pt = _conv(t->tm_mon + 1, "%02d", pt, ptlim);
          continue;
/*
        case 'n':
          pt = _add("\n", pt, ptlim);
          continue;

*/
        case 'P':
          pt = _add((t->tm_hour >= 12) ? "PM" : "AM", pt, ptlim);
          continue;

        case 'p':
          pt = _add((t->tm_hour >= 12) ? "pm" : "am", pt, ptlim);
          continue;
/*
        case 'R':
          pt = _fmt("%H:%M", t, pt, ptlim);
          continue;

        case 'r':
          pt = _fmt("%I:%M:%S %P", t, pt, ptlim);
          continue;
*/
        case 'S':
          pt = _conv(t->tm_sec, "%02d", pt, ptlim);
          continue;
/*
        case 'T':
          pt = _fmt("%H:%M:%S", t, pt, ptlim);
          continue;

        case 't':
          pt = _add("\t", pt, ptlim);
          continue;
*/
        case 'U':
          pt = _conv((t->tm_yday + 7 - t->tm_wday) / 7, "%02d", pt, ptlim);
          continue;
/*
        case 'u':
          pt = _conv((t->tm_wday == 0) ? 7 : t->tm_wday, "%d", pt,
              ptlim); continue;

        case 'v':
          pt = _fmt("%e-%b-%Y", t, pt, ptlim);
          continue;
*/
        case 'W':
          pt = _conv((t->tm_yday + 7 - (t->tm_wday ? (t->tm_wday - 1) : 6)) / 7,
                     "%02d", pt, ptlim);
          continue;

        case 'w':
          pt = _conv(t->tm_wday, "%d", pt, ptlim);
          continue;

        case 'X':
          pt = _fmt("%H:%M:%S", t, pt, ptlim);
          continue;

        case 'x':
          pt = _fmt("%m/%d/%y", t, pt, ptlim);
          continue;

        case 'y':
          pt = _conv((t->tm_year + 1900) % 100, "%02d", pt, ptlim);
          continue;

        case 'Y':
          pt = _conv(t->tm_year + 1900, "%04d", pt, ptlim);
          continue;

        case 'z': {
          tz_hr = int_from_i32(
            divi32(_tz_offset, i32_from_int(SECS_PER_HOUR), &tz_sec));

          if (tz_hr < 0) {
            pt = _add("-", pt, ptlim);
          } else {
            pt = _add("+", pt, ptlim);
          }

          pt = _conv(abs(tz_hr), "%02d", pt, ptlim);
          pt = _conv(int_from_i32(tz_sec) / SECS_PER_MIN, "%02d", pt, ptlim);

          continue;
        }

        case 'Z':
          pt = _add(_tzname ? _tzname : "?", pt, ptlim);
          continue;

        case '%':
        default:
          break;
      }
    }

    if (pt == ptlim) break;
    *pt++ = *format;
  }

  return pt;
}

int _strftime(char *s, int maxsize, const char *format, struct tm *tp)
{
  char *p;

  p = _fmt(((format == NULL) ? "%c" : format), tp, s, s + maxsize);
  if (p == s + maxsize) return 0;
  *p = '\0';
  return p - s;
}
