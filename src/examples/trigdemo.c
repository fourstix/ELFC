#define _STGROM_
#include <stdio.h>
#include <float32.h>

char    abuf[16];
char    vbuf[16];
char    a2buf[16];
/* test angles */
/*
float32_t fp_zero    = {0x0000, 0x0000};
float32_t fp_6thpi   = {0x0a92, 0x3f06};
float32_t fp_4thpi   = {0x0fdb, 0x3f49};
float32_t fp_3rdpi   = {0x0a92, 0x3f86};
float32_t fp_halfpi  = {0x0fdb, 0x3fc9};
float32_t fp_pi      = {0x0fdb, 0x4049};
float32_t fp_3halfpi = {0xcbe4, 0x4096};
float32_t fp_2pi     = {0x0fdb, 0x40c9};
*/

char *anames[4] = {"0", "pi/6", "pi/4", "pi/3"};
char *qnames[4] = {"", "pi/2", "pi", "3pi/2"};
float32_t angles[4] = {{0x0000, 0x0000}, {0x0a92, 0x3f06}, {0x0fdb, 0x3f49}, {0x0a92, 0x3f86}};
float32_t quad_offset[3] = {{0x0fdb, 0x3fc9}, {0x0fdb, 0x4049}, {0xcbe4, 0x4096}};

void showtrig(float32_t a) {
  float32_t x, a2;
  ftoa(a, abuf);
  printf("Angle = %s\n", abuf);

  x = sinf(a);
  ftoa(x, vbuf);
  printf("sinf(%s) = %s\n", abuf, vbuf);
  a2 = asinf(x);
  ftoa(a2, a2buf);
  printf("asinf(%s) = %s\n", vbuf, a2buf);

  x = cosf(a);
  ftoa(x, vbuf);
  printf("cosf(%s) = %s\n", abuf, vbuf);
  a2 = acosf(x);
  ftoa(a2, a2buf);
  printf("acosf(%s) = %s\n", vbuf, a2buf);

  x = tanf(a);
  ftoa(x, vbuf);
  printf("tanf(%s) = %s\n", abuf, vbuf);
  a2 = atanf(x);
  ftoa(a2, a2buf);
  printf("atanf(%s) = %s\n", vbuf, a2buf);
}

int main() {
  int i, j;
  float32_t angle, offset;
  for (i = 0; i < 4; i++) {
    printf("\nQuadrant %d:\n", i+1);
    for(j = 0; j < 4; j++) {
      angle = angles[j];
      /* first quadrant has no offset */
      if (i) {
        offset = quad_offset[i-1];
        if (j)
          angle = addf(angle, offset);
        else
          angle = offset;
      }
      printf("\n%s+%s:\n", qnames[i], anames[j]);
      showtrig(angle);
    }
  }
  return 0;
}
