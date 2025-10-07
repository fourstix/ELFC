#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrlen

/* Reverse a string in place
 *
 * Based on the example on page 62 of
 * The C Programming Language, 2nd edition
 * by Brian W. Kernighan and Dennis M. Ritchie
 * Copyright 1988 by Prentice Hall
 */
void reverse(char *s) {
  int c, i, j;
  
  if (s == NULL) return;
  
  for(i = 0, j = strlen(s)-1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}
