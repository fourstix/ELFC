#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "kdir.h"

#pragma             extrn Cerrno
#pragma             extrn C_kpathres
#pragma             extrn C_kdiropen
#pragma             extrn C_kdirread
#pragma             extrn C_kdirsave
#pragma             extrn C_kdirrestore

/*
 * Return the next entry of an open directory, or NULL at the end of
 * the directory.  errno is set to EBADF for a NULL DIR, or to EIO if
 * the directory's drive can no longer be read; it is left unchanged
 * at the end of the directory.  The entry is overwritten by the next
 * readdir on the same DIR.
 *
 * The kernel has one directory scan, shared by every program and by
 * calls like K_STAT and K_FILE_OPEN, and it reads whichever drive was
 * resolved last.  So each call selects the directory's drive again
 * by resolving "X:/", then starts the scan or restores the position
 * saved by the call before, reads one entry and saves the position.
 */
struct dirent *readdir(DIR *dirp) {
  struct dirent *de;
  unsigned char *p;
  unsigned int clust;
  char *name;
  int drive;
  unsigned char attr;
  unsigned int ino;
  unsigned int szhi;
  unsigned int szlo;
  unsigned int tm;
  unsigned int dt;

  if (dirp == NULL) {
    errno = EBADF;
    return NULL;
  }

  if (dirp->dd_eof)
    return NULL;

  if (_kpathres(dirp->dd_root, &clust, &name, &drive) == EOF) {
    dirp->dd_eof = 1;
    errno = EIO;
    return NULL;
  }

  if (dirp->dd_loc == 0) {
    _kdiropen(dirp->dd_clust);
  } else if (_kdirrestore(dirp->dd_state) == EOF) {
    dirp->dd_eof = 1;
    errno = EIO;
    return NULL;
  }

  de = &dirp->dd_ent;
  p = (unsigned char *) de;

  if (_kdirread(p) == EOF) {
    dirp->dd_eof = 1;
    return NULL;
  }

  _kdirsave(dirp->dd_state);
  dirp->dd_loc++;

  /*
   * Convert the kernel's big-endian fields, which follow the name, to
   * the struct dirent fields.  They overlap, so read them all first.
   */
  attr = p[_KD_ATTR];
  ino  = (p[_KD_CLUST] << 8) | p[_KD_CLUST + 1];
  szhi = (p[_KD_SIZE] << 8) | p[_KD_SIZE + 1];
  szlo = (p[_KD_SIZE + 2] << 8) | p[_KD_SIZE + 3];
  tm   = (p[_KD_TIME] << 8) | p[_KD_TIME + 1];
  dt   = (p[_KD_DATE] << 8) | p[_KD_DATE + 1];

  de->d_attr = attr;
  de->d_ino = ino;
  de->d_size.high = szhi;
  de->d_size.low = szlo;
  de->d_time = tm;
  de->d_date = dt;

  return de;
}
