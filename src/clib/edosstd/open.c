#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "edos.h"

#pragma             extrn Cerrno
#pragma             extrn C_fdinit
#pragma             extrn C_fdtable
#pragma             extrn Cfree
#pragma             extrn Cclose
#pragma             extrn Clseek

/*
 *  The open flags keep their Elf/OS values, and are mapped onto the
 *  three ELF-DOS open modes:
 *
 *    O_RDONLY             read only, the file must exist
 *    O_TRUNC              read and write, the file is emptied
 *    otherwise            read and write, the contents are kept
 *
 *  ELF-DOS creates a missing file in both write modes, so without
 *  O_CREAT the file is looked up first.  ELF-DOS keeps the contents of
 *  a file only when it is opened for append, so without O_APPEND the
 *  file is moved back to its start after it is opened.
 */

int	open(char *path, int flags) {
  int fildes;
  int fd;
  int result;
  int mode;

  if (flags & O_RDONLY)
    mode = _K_READ;
  else if (flags & O_TRUNC)
    mode = _K_WRITE;
  else
    mode = _K_APPEND;

  /* create file descriptor for system file */
  fd = _fdinit();

  if (fd == EOF)
    return EOF;

  /* get system file descriptor */
  fildes = _fdtable[fd];

  result = 0;

  /* without the create flag, the file must already exist */
  if (mode != _K_READ && !(flags & O_CREAT)) {
    asm("         gosub s_lget16  ; get the name argument ");
    asm("           dw 0          ; get from argument stack");
    asm("         copy ra, rf     ; copy path argument as name buffer");
    asm("         gosub s_lget16  ; get the fildes argument ");
    asm("           dw -2         ; get from the local variable");
    asm("         glo  ra         ; sector buffer is 32 bytes after fildes");
    asm("         adi  FCB_LEN    ; it is not in use yet, so it can");
    asm("         plo  rd         ; hold the directory information");
    asm("         ghi  ra         ; propagate carry into hi byte");
    asm("         adci 0          ; add carry bit to hi byte");
    asm("         phi  rd         ; rd now points to sector buffer");
    _KSAVE
    asm("         call K_STAT     ; attempt to find the file");
    _KRESTORE
    _KRESULT
    asm("         gosub s_lset16  ; set result argument ");
    asm("           dw -6         ; in the local variable on the stack");
  }

  if (result != EOF) {
    asm("         gosub s_lget16  ; get the mode variable ");
    asm("           dw -8         ; get from the local variable");
    asm("         copy ra, rc     ; save mode for open");
    asm("         gosub s_lget16  ; get the name argument ");
    asm("           dw 0          ; get from argument stack");
    asm("         copy ra, rf     ; copy path argument as name buffer");
    asm("         gosub s_lget16  ; get the fildes argument ");
    asm("           dw -2         ; get from the local variable");
    asm("         copy ra, rd     ; copy fildes pointer to fcb pointer");
    asm("         glo  rd         ; sector buffer is 32 bytes after fildes");
    asm("         adi  FCB_LEN");
    asm("         plo  ra         ; put lo byte into ra");
    asm("         ghi  rd         ; propagate carry into hi byte");
    asm("         adci 0          ; add carry bit to hi byte");
    asm("         phi  ra         ; ra now points to sector buffer");
    _KSAVE
    asm("         glo  rc         ; set mode for open");
    asm("         call K_FILE_OPEN ; attempt to open the file");
    _KRESTORE
    _KRESULT
    asm("         gosub s_lset16  ; set result argument ");
    asm("           dw -6         ; in the local variable on the stack");
  }

  /* if open failed, set errno and undo _fdinit */
  if (result == EOF) {
    errno = EIO;
    /* free the system file descriptor in memory */
    free((void *) _FCB_BLOCK(fildes));
    /* mark the entry in the table as unused */
    _fdtable[fd] = EOF;
    return EOF;
  }

  /* an append open is left at the end of the file, so rewind it */
  if (mode == _K_APPEND && !(flags & O_APPEND)) {
    if (lseek(fd, 0, SEEK_SET) == -1) {
      close(fd);
      errno = EIO;
      return EOF;
    }
  }

  return fd;
}
