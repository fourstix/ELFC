#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* time structure */
static struct tm now; 
/* pointer to structure */
struct tm* tp;

/* buffer for strftime */
char tbuf[64];

int main() {
  int retval;
  char *p;

  /* set pointer for tests */

  tp = &now;

  /* set local timezone for US Eastern Daylight Time */
  timezone("EDT", -300, 1);
  
  /* Get the system time */
  retval = systime(tp); 

  printf("%02d:%02d:%02d %02d/%02d/%04d\n",
    tp->tm_hour, tp->tm_min, tp->tm_sec,
    tp->tm_mon+1, tp->tm_mday, tp->tm_year+1900);

  printf("Day of week: %d  Day of Year: %d\n", tp->tm_wday, tp->tm_yday+1);
  
  if (tp->tm_isdst)
    printf("Daylight Savings Time.\n");
  else
     printf("Standard Time.\n");

  printf("Source: %s\n", retval ? "RTC" : "Kernel");
  
  printf("Ascii %s", asctime(tp));
  
  printf("CStime: %s", cstime());
  
  strftime(tbuf, 64, "%A %Y-%m-%d %H:%M:%S %Z", tp);
  printf("Local time: %s\n", tbuf);
  
  /* Get GMT time */
  utctime(tp);
  
  printf("GMT: %02d:%02d:%02d %02d/%02d/%04d\n",
    tp->tm_hour, tp->tm_min, tp->tm_sec,
    tp->tm_mon+1, tp->tm_mday, tp->tm_year+1900);

  printf("GMT Day of week: %d  GMT Day of Year: %d DST: %d\n", tp->tm_wday, tp->tm_yday+1, tp->tm_isdst);
  
  /* time zone name for UTC is Z for Zulu */
  strftime(tbuf, 64, "%A %Y-%m-%d %H:%M:%S Z", tp);
  printf("GMT time: %s\n", tbuf);
}
