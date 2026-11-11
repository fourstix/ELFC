#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "odir.h"

#pragma             extrn C_fdinit
#pragma             extrn C_fdtable
#pragma             extrn Cfree
#pragma             extrn C_oopendir

/*
 * Open a directory as a file in a new C library file descriptor.
 * Returns the file descriptor, or -1 if there is no free descriptor
 * (errno is set by _fdinit) or O_OPENDIR fails (errno is not set).
 */
int _odiropen(char *path) {
  int fd;
  int fildes;

  fd = _fdinit();
  if (fd == EOF)
    return EOF;
  fildes = _fdtable[fd];

  if (_oopendir(path, (unsigned char *) fildes) == EOF) {
    free((void *) fildes);
    _fdtable[fd] = EOF;
    return EOF;
  }

  return fd;
}
