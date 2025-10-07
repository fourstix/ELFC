#define _ELFCLIB_
#include <stdio.h>

#pragma             extrn Cfgetpos

int ftell(FILE *f) {
  int   val;
  pos_t position;
  pos_t *pos;
  
  pos = &position;
  /* any return value but zero is an error */
  val = fgetpos(f, pos);
  
  /* return -1 if error or position out of range */
  if (val || (pos->hi != 0) || (pos->lo < 0)) {
    return EOF;
  } 
  
  return pos->lo;
  }
  
  
