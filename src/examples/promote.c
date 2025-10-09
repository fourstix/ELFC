#include <stdio.h>

unsigned char uc =  77;
signed char   sc = -7;


unsigned int  ui1 =  7;
signed int    i   = -77;

int main() {
  char c;
  unsigned int ui2;

  c = uc + sc;
  ui2 = ui1 + i;

  printf("char c = '%c' (%d)\n", c,c);
  printf("unsigned int ui2 = %u (%#x%)\n", ui2, ui2);
}
