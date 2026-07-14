#include <stdio.h>
#include <time.h>
#include <float32.h>

/* 365.25 days in average year */
float32_t Doy = {0xa000, 0x43b6};
/* 30.6 days in average month */
float32_t Dom = {0xcccd, 0x41f4};
/* Reference starts with new moon at 1900 Jan 1 (jd = 694039.09) */
float32_t Epoch = {0x7171, 0x4929};
/* Lunation cycle (29.53 days) */
float32_t Cycle = {0x3d71, 0x41ec};
/* Eight phases */
float32_t Eight = {0x0000, 0x4100};

/*
 * Calculate the phase of the moon
 */
int moon_phase(int y, int m, int d) {
  static float32_t tmp;
  //static float32_t tmp2;
  static float32_t jd;
  int b;

  if (m < 3) {
    y--;
    m += 12;
  }
  ++m;
  /* calculate days for the years in date */
  tmp = itof(y);
  tmp = mulf(tmp, Doy);
  jd = truncf(tmp);
  /* calculate days for the months in date */
  tmp = itof(m);
  tmp = mulf(tmp, Dom);
  tmp = truncf(tmp);
  jd = addf(jd, tmp);
  /* add days for date */
  tmp = itof(d);
  jd = addf(jd, tmp);
  /* jd is total days elapsed since epoch */
  jd = subf(jd, Epoch);
  /* Calculate lunation cycles since epoch (29.53 days) */
  jd = divf(jd, Cycle);
  /* The fractional part of the lunation number gives the phase */
  jd = fracf(jd);
  /* scale fraction and round to phase number */
  jd = mulf(jd, Eight);
  jd = roundf(jd);
  /* 0 to 7 are valid phase numbers */
  b = ftoi(jd);
  b &= 7;
  return b;
}

/*
 * Get the name of the moon's phase
 */
char *moon_name(int p) {
  switch (p) {
    case 0:
      return "New";
    case 1:
      return "Waxing Crescent";
    case 2:
      return "First Quarter";
    case 3:
      return "Waxing Gibbous";
    case 4:
      return "Full";
    case 5:
      return "Waning Gibbous";
    case 6:
      return "Last Quarter";
    case 7:
      return "Waning Crescent";
  }
}

int main() {
  int p;
  char *moon;
  struct tm now;
  /* set the timezone for Eastern Daylight Time */
  timezone("EDT", -240, 1);
  systime(&now);

  /* Calculate the phase for tonight's moon */
  p = moon_phase(now.tm_year + 1900, now.tm_mon + 1, now.tm_mday);
  moon = moon_name(p);
  printf("There is a %s moon tonight.\n", moon);
}
