#include <stdio.h>

/*
 * Demo of various conversion formats
 */
int i = 50;
int j = -300;

char str[] = "string";

int main() {

  printf("Int formats:\n");
  printf("plain: _%d_%d_\n", i, j);
  printf("+ flag: _%+d_%+d_\n", i, j);
  printf("size 4: _%4d_%4d_\n", i, j);
  printf("04 flag: _%04d_%04d_\n", i, j);
  printf("-4 flag: _%-4d_%-4d_\n", i, j);
  printf(" 4 flag: _% 4d_% 4d_\n", i, j);
  printf("+04: _%+04d_%+04d_\n", i, j);


  printf("Int 06:%06i!\n", 3);

  printf("Pointer %p and string %s\n", str, str);
  printf("Character %c %c\n", 'q', *str); 
  printf("Hex %x %X\n", i, j);
  printf("Alt Hex: %#x %#X\n", i, j);
  printf("Octal %o %o\n", i, j);
  printf("Alt Octal %#o %#o\n", i, j);
  printf("Number characters written so far: %n\n");
  printf("Escape for %% sign\n");

}
