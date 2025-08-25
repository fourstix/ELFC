#include <stdio.h>
#include <limits.h>

char fname[20];
int  i;
char ch;

main() {
  int j;
  char *p;
  
  p = fname;
  

  printf("Enter an integer number (between %d and %d): ", INT_MIN, INT_MAX);
  scanf("%d", &i);
  printf("\nYou entered %i\n", i);
  
  printf("What is your first name?\n");
  scanf("%19s", fname);
  printf("\nHello, %s!\n", fname);
  
  printf("Enter a hexadecimal number:\n");
  scanf("%x", &i); 
  printf("\nYou entererd %#x\n", i);
  
  printf("Enter an octal number:\n");
  scanf("%o", &i); 
  printf("\nYou entererd %#o\n", i);
  
  printf("Enter a non-space character:\n");
  scanf(" %c", &ch);
  
  printf("\nYou entererd '%c' (%d)\n", ch, ch);
  
  printf("Enter any five characters:\n");
  scanf("%5c", p);
  
  /* put a null after 5 characters to create a string */
  fname[5] = 0; 
  printf("\nYou entered %s\n", p);
  
  printf("\nScanset: numbers only:\n");
  scanf(" %19[0-9]", p);
  printf("\nYou entered %s\n", p);

  printf("\n^Scanset: no capital letters:\n");
  scanf(" %19[^A-Z]", p);
  printf("\nYou entered %s\n", p);
  
}
