#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "kdir.h"

#pragma             extrn Cerrno
#pragma             extrn C_kfill

/*
 * Return the next entry of an open directory, or NULL at the end of
 * the directory.  errno is set to EBADF for a NULL DIR, or to EIO if
 * the directory's drive can no longer be read; it is left unchanged
 * at the end of the directory.  The entry may be overwritten by the
 * next readdir or rewinddir on the same DIR.
 *
 * Entries are read ahead by _kfill, up to dd_nslots at a time, so the
 * kernel's scan position is restored once for each group of entries.
 */
struct dirent *readdir(DIR *dirp) {
  int n;

  if (dirp == NULL) {
    errno = EBADF;
    return NULL;
  }

  if (dirp->dd_i >= dirp->dd_n) {
    if (dirp->dd_eof)
      return NULL;
    dirp->dd_i = 0;
    dirp->dd_n = 0;
    n = _kfill(dirp);
    if (n == EOF) {
      dirp->dd_eof = 1;
      errno = EIO;
      return NULL;
    }
    if (n == 0)
      return NULL;
    dirp->dd_n = n;
  }

  return &dirp->dd_slot[dirp->dd_i++];
}
