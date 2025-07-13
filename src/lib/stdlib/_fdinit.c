#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno

#ifndef FD_SIZE
#define FD_SIZE   532
#endif

#ifndef FD_MAX
#define FD_MAX   4
#endif

static int _fdcnt = 0;
#pragma             public C_fdcnt   

#pragma             extrn Cmalloc    

int _fdinit(void) {
  int fd;
  
  if (_fdcnt >= FD_MAX) {
      errno = EMFILE;
      return EOF;
    }
  
  
  fd = (int) malloc(FD_SIZE);
  
  /* if malloc failed return error */
  if (fd == 0) {
    errno = ENOMEM;
    return EOF;
  }
  
  /* set up fd format */
  asm("         call lget16     ; get the fd buffer pointer");
  asm("           dw -2         ; get pointer from argument stack");           
  asm("         copy ra, rf     ; copy fd pointer to buffer pointer");
  asm("         copy ra, rd     ; copy fd pointer to dta pointer");
  asm("         glo  rd         ; dta is 20 bytes after filedes");
  asm("         adi  20");
  asm("         plo  rd         ; put lo byte into rd");
  asm("         ghi  rd         ; propagate carry into hi byte");
  asm("         adci 0          ; add carry bit to hi byte");
  asm("         phi  rd         ; rd now points to dta"); 
  asm("         ldi  0          ; zero out first four bytes of filedes");
  asm("         str  rf");
  asm("         inc  rf"); 
  asm("         str  rf");
  asm("         inc  rf"); 
  asm("         str  rf");
  asm("         inc  rf"); 
  asm("         str  rf");
  asm("         inc  rf         ; move rr to dta value in filedes"); 
  asm("         ghi  rd         ; put dta address hi byte next");
  asm("         str  rf");
  asm("         inc  rf");
  asm("         glo  rd         ; put dta address hi byte next");
  asm("         str  rf");
  asm("         inc  rf");
  asm("         ldi  $0E        ; zero out next 14 bytes");
  asm("         plo  rc         ; set up counter");
  asm("fd_rpt:  ldi  0");
  asm("         str  rf         ; zero out next byte");
  asm("         inc  rf");
  asm("         dec rc          ; count down");
  asm("         glo rc          ; check if counter has gone to zero");
  asm("         lbnz fd_rpt     ; if not keep going");
  
  _fdcnt++;            
  return fd;
} 
