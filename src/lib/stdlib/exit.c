#include "_stdlib.h"
#pragma           extrn Elfexit
void exit(int n) {
    asm("         call  lget16      ; set error return code for exit");
    asm("           dw  -2          ");
    asm("         clc               ; clear DF for exit");
    asm("         lbr   Elfexit     ; exit immediately from program");
  }
