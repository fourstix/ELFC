#define _ELFCLIB_
#include <stdlib.h>
#include "odir.h"

/*
 * Open a directory as a file with O_OPENDIR, using the system file
 * descriptor fildes.  Returns 0, or -1 if the path is not found or is
 * not a directory.
 *
 * Elf/OS 4 does not use the file descriptor it is given.  It returns
 * its own in RD, which the next open overwrites, so that descriptor
 * is copied into fildes, all but fildes's own DTA pointer, and so is
 * its DTA.  This is what the Mini/DOS dir command does.  O_OPENDIR is
 * called by its address, since it is not in older os_api.inc files.
 */
int _oopendir(char *path, unsigned char *fildes) {
  int result;
  unsigned char *sysfd;
  unsigned char *src;
  unsigned char *dst;
  int i;

  asm("         gosub s_lget16  ; get the fildes argument ");
  asm("           dw 2          ; from argument stack");
  asm("         copy ra, rd     ; copy fildes to file descriptor pointer");
  asm("         gosub s_lget16  ; get the path argument ");
  asm("           dw 0          ; from argument stack");
  asm("         copy ra, rf     ; copy path string to name pointer");
  asm("         push r7         ; save ESP");
  asm("         push r9         ; Elf/OS 4 O_OPENDIR changes r9");
  asm("         push rb         ; save stack frame base pointer");
  asm("         call 0315h      ; O_OPENDIR, open directory as a file");
  asm("         pop  rb         ; restore stack frame base pointer");
  asm("         pop  r9         ; restore subroutine pointer");
  asm("         pop  r7         ; restore ESP");
  asm("         ldi  0          ; set default value for success");
  asm("         lsnf            ; DF = 0, means success");
  asm("         ldi  $Ff        ; otherwise set result for error");
  asm("         phi  ra         ; set result to 0 or -1 ");
  asm("         plo  ra         ; set result in ra ");
  asm("         gosub s_lset16  ; set the result variable ");
  asm("           dw -2         ; in the local variable on the stack");
  asm("         copy rd, ra     ; file descriptor that was opened");
  asm("         gosub s_lset16  ; set the sysfd variable ");
  asm("           dw -4         ; in the local variable on the stack");

  if (result != EOF && sysfd != fildes) {
    for (i = 0; i < 19; i++)
      if (i != _FD_DTA && i != _FD_DTA + 1)
        fildes[i] = sysfd[i];
    src = (unsigned char *) ((sysfd[_FD_DTA] << 8) | sysfd[_FD_DTA + 1]);
    dst = (unsigned char *) ((fildes[_FD_DTA] << 8) | fildes[_FD_DTA + 1]);
    for (i = 0; i < _FD_DTALEN; i++)
      dst[i] = src[i];
  }

  return result;
}
