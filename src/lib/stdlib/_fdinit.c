#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>

#pragma             extrn Cerrno

static int _fdcnt = 0;

#pragma             public C_fdcnt   
#pragma             extrn Cmalloc    

/* 
 *  Elf/OS File Descriptor Layout
 * --------------------------------
 *  Byte : Desicription      : Length
 * --------------------------------
 *   0-3 : Current Offset    :  4
 *   4-5 : DTA Pointer       :  2
 *   6-7 : EOF               :  2
 *   8   : Flags Byte        :  1
 *  9-12 : DIR Sector        :  4
 * 13-14 : DIR Offset        :  2
 * 15-18 : Current Sector    :  4
 *   19  : Drive Number (v5) :  1
 *   20  : Drive FStype (v5) :  1
 *   21  : 1 byte padding    :  1
 *    Header Total = 22 bytes   
 * --------------------------------
 *          DTA (512 Bytes)
 * --------------------------------
 *   Total FD size = 534 bytes
 */

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
  asm("         glo  rd         ; dta is 22 bytes after filedes");
  asm("         adi  22");
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
  asm("         inc  rf         ; move to dta value in filedes"); 
  asm("         ghi  rd         ; put dta address hi byte next");
  asm("         str  rf");
  asm("         inc  rf");
  asm("         glo  rd         ; put dta address hi byte next");
  asm("         str  rf");
  asm("         inc  rf");
  asm("         ldi  $10        ; zero out next 16 bytes");
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
