#define _ELFCLIB_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* define only extern procedures required */
#pragma           extrn Csprintf

/*
 * Generate the standard ASCII date-time string 
 */
char *asctime(struct tm *tp) {
	static char	buf[26];
	char	 *days, *months;

	days = "Sun\0Mon\0Tue\0Wed\0Thu\0Fri\0Sat";
	months = "Jan\0Feb\0Mar\0Apr\0May\0Jun\0Jul\0Aug\0Sep\0Oct\0Nov\0Dec";
	
	sprintf(buf, "%s %s %2d %2d:%02d:%02d %04d\n",
		days + (tp->tm_wday)*4, months + (tp->tm_mon)*4, tp->tm_mday,
		tp->tm_hour, tp->tm_min, tp->tm_sec,	tp->tm_year+1900);
	
	/* Make sure buffer ends in zero */	
	buf[25] = 0;	
	return buf;
}
