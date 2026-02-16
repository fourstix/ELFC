#define _ELFCLIB_
#include <stdio.h>
#include <errno.h>


#pragma             extrn Cerrno
#pragma             extrn C_fildes


int fgetpos(FILE *f, pos_t *pos) {
  int fildes;
  int hi;
  int lo;
  int result;
  
  if (f == NULL || pos == NULL) {
    errno = EINVAL;
    return -1;
  }
  
  /* can't get position of an system IO stream */
  if (f->mode == _IOSYS) {
    errno = EBADF;
    return -1;
  }
  
  /* set initial values for local variables */
  hi = 0;
  lo = 0;
  
  /* get system file descriptor */
  fildes = _fildes(f->fd);
  
  asm("         gosub s_lget16  ; get the fd argument ");
  asm("           dw -2         ; from argument stack");           
  asm("         copy ra, rd     ; copy fd to fildes register");
  asm("         ldi  0          ; set position hi byte to zero");
  asm("         phi rc          ; set hi byte for current position ");
  asm("         ldi  1          ; set position lo byte to one");
  asm("         plo  rc         ; to seek from the current position ");
  asm("         push r7         ; save stack pointer");
  asm("         ldi  0          ; set offset value to zero");
  asm("         plo  r8         ; set low byte of hi word offset register");           
  asm("         phi  r8         ; set high byte of hi word offset register");
  asm("         plo  r7         ; set low byte of lo word offset register");           
  asm("         phi  r7         ; set high byte of lo word offset register");
  asm("         call O_SEEK     ; attempt to seek within file");
  asm("         copy r7, rc     ; save low position word");
  asm("         pop  r7         ; restore expression stack pointer immediately");
  asm("         copy r8, rd     ; save high position word");
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result for 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         gosub s_lset16  ; set the result ");
  asm("           dw -8         ; in the local variable");           
  asm("         copy rd, ra     ; save high position word");
  asm("         gosub s_lset16  ; set the hi word result ");
  asm("           dw -4         ; in the local variable");           
  asm("         copy rc, ra     ; save low position word");
  asm("         gosub s_lset16  ; set the lo word result ");
  asm("           dw -6         ; in the local variable");           
  
  /* adjust for any character in pushback buffer from previous read*/
  if (_FREAD == f->last) {
    if (f->ch != EOF) {
      lo--;
      /* adjust double word (32-bit) value */ 
      /* if lo was zero before, then decrement hi byte */
      if (-1 == lo)
        hi--;
    }
  }

  pos->high = hi;
  pos->low = lo;

  return result;
}
