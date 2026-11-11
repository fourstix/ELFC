#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "odir.h"

#pragma             extrn Cerrno
#pragma             extrn Cclose
#pragma             extrn Cfree

/*
 * Close an open directory.  Returns 0, or -1 with errno EBADF for
 * NULL or EIO if the directory's file descriptor did not close.
 */
int closedir(DIR *dirp) {
  int result;

  if (dirp == NULL) {
    errno = EBADF;
    return EOF;
  }

  result = close(dirp->dd_fd);
  free(dirp->dd_path);
  free(dirp);

  if (result == EOF) {
    errno = EIO;
    return EOF;
  }
  return 0;
}
