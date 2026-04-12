#define _STGROM_
#include <stdio.h>


int main() {
  int i1, i2;
  unsigned int u1, u2;

  char c;
  signed char s;

  i1 = -23;
  c = (char) i1;
  s = (signed char) i1;
  printf("i = %d (%#x), (char)i = %d (%#x)\n", i1, i1, c, c);
  printf("i = %d (%#x), (signed char)i = %d (%#x)\n", i1, i1, s, s & 0x00ff);

  i2 =  84;
  c = (char) i2;
  s = (signed char) i2;


  printf("i = %d (%#x), (char)i = %d (%#x)\n", i2, i2, c, c);
  printf("i = %d (%#x), (signed char)i = %d (%#x)\n", i2, i2, s, s & 0x00ff);

  i1 = 1089;
  c = (char) i1;
  s = (signed char) i1;

  printf("i = %d (%#x), (char)i = %d (%#x)\n", i1, i1, c, c);
  printf("i = %d (%#x), (signed char)i = %d (%#x)\n", i1, i1, s, s & 0x00ff);

  i2 = -663;
  c = (char) i2;
  s = (signed char) i2;

  printf("i = %d (%#x), (char)i = %d (%#x)\n", i2, i2, c, c);
  printf("i = %d (%#x), (signed char)i = %d (%#x)\n", i2, i2, s, s & 0x00ff);

  i1 = 4096;
  c = (char) i1;
  s = (signed char) i1;

  printf("i = %d (%#x), (char)i = %d (%#x)\n", i1, i1, c, c);
  printf("i = %d (%#x), (signed char)i = %d (%#x)\n", i1, i1, s, s & 0x00ff);

  i2 = 16534;
  c = (char) i2;
  s = (signed char) i2;

  printf("i = %d (%#x), (char)i = %d (%#x)\n", i2, i2, c, c);
  printf("i = %d (%#x), (signed char)i = %d (%#x)\n", i2, i2, s, s & 0x00ff);

  c = 64;
  s = 64;

  i1 = (int) c;
  i2 = (int)s;

  printf("unsigned char c = %d (%#x), (int)c = %d (%#x)\n", c, c, i1, i1);
  printf("signed char s = %d (%#x), (int)s = %d (%#x)\n", s, s & 0x00ff, i2, i2);

  u1 = (unsigned) c;
  u2 = (unsigned) s;

  printf("unsigned char c = %d (%#x), (unsigned int)c = %d (%#x)\n", c, c, u1, u1);
  printf("signed char s = %d (%#x), (unsigned int)s = %d (%#x)\n", s, s & 0x00ff, u2, u2);

  c = 134;
  s = -122;

  i1 = (int) c;
  i2 = (int)s;

  printf("unsigned char c = %d (%#x), (int)c = %d (%#x)\n", c, c, i1, i1);
  printf("signed char s = %d (%#x), (int)s = %d (%#x)\n", s, s & 0x00ff, i2, i2);

  u1 = (unsigned) c;
  u2 = (unsigned) s;

  printf("unsigned char c = %d (%#x), (unsigned int)c = %u (%#x)\n", c, c, u1, u1);
  printf("signed char s = %d (%#x), (unsigned int)s = %u (%#x)\n", s, s & 0x00ff, u2, u2);
}
