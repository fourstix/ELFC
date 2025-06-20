#include "_stdlib.h"
#pragma           extrn Elfexit
void abort(void) {
    asm("         load  ra, -1      ; set error return code for exit");
    asm("         stc               ; set DF for exit");
    asm("         lbr   Elfexit     ; exit immediately from program");
  }
