#include <stdio.h>

/*
 * Demo of various conversion formats
 */
int i = 50;
int j = -300;

char str[] = "string";
unsigned int u = 65000;

int main() {

  printf("Int formats %%d %%i:\n");
  printf("plain: _%d_%i_\n", i, j);
  printf("+ flag: _%+d_%+i_\n", i, j);
  printf("size 4: _%4i_%4d_\n", i, j);
  printf("04 flag: _%04d_%04i_\n", i, j);
  printf("-4 flag: _%-4i_%-4d_\n", i, j);
  printf(" 4 flag: _% 4d_% 4i_\n", i, j);
  printf("+04: _%+04i_%+04d_\n", i, j);

  printf("Unsigned Int %%u format:\n");
  printf("plain: %u\n", u);
  printf("+ flag: (ignored): %+u\n", u);
  printf("size 6: _%6u_\n", u);
  printf("06 flag: _%06u_\n", u);
  printf("-6 flag: _%-6u_\n", u);

  /* Other formats */
  printf("Pointer %p and string %s\n", str, str);
  printf("Character: %c %c\n", 'q', *str);
  printf("Hex: %x %X\n", u, j);
  printf("Alt Hex: %#x %#X\n", u, j);
  printf("Octal: %o %o\n", i, j);
  printf("Alt Octal: %#o %#o\n", i, j);
  printf("* size (5) as parameter _%*d_\n", 5, i);
  printf("Number characters written so far: %n\n");
  printf("Escape for %% sign\n");
}
