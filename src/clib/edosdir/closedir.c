#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "kdir.h"

#pragma             extrn Cerrno
#pragma             extrn Cfree

/* Close an open directory.  Returns 0, or -1 with errno EBADF for NULL */
int closedir(DIR *dirp) {
  if (dirp == NULL) {
    errno = EBADF;
    return EOF;
  }

  free(dirp);
  return 0;
}
