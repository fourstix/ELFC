#define _ELFCLIB_
#include <stdlib.h>
#include <stdio.h>


#pragma           .link .requires Catexit
#pragma           extrn C_exitfn
#pragma           extrn C_files
#pragma           extrn Cfclose
#pragma           extrn Elfexit

extern int	(*_exitfn)();
extern FILE	*_files[];

void exit(int n) {
  
  if (_exitfn) _exitfn();

/*
  for (i = 3; i < FOPEN_MAX; i++) {
    fclose(_files[i]);
  }
*/  
  asm("         call  lget16      ; set error return code for exit");
  asm("           dw  0           ; get return value from argument stack");
  asm("         clc               ; clear DF for exit");
  asm("         lbr   Elfexit     ; exit immediately from program");
}
