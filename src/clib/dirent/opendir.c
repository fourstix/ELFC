#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "odir.h"

#pragma             extrn Cerrno
#pragma             extrn Cmalloc
#pragma             extrn Cfree
#pragma             extrn C_fdinit
#pragma             extrn C_fdtable
#pragma             extrn Copen
#pragma             extrn Cclose
#pragma             extrn C_oopendir

/*
 * Open a directory for reading.  Returns NULL and sets errno to
 * ENOENT when the path is not found, ENOTDIR when it names a file,
 * ENOMEM when there is no memory, EMFILE when there is no free file
 * descriptor, or EINVAL for NULL.
 *
 * The directory is opened as a file with O_OPENDIR, in a file
 * descriptor from the C library's table, and read with read().  The
 * path is kept so readdir can open each file to find its size.
 */
DIR *opendir(const char *path) {
  DIR *dirp;
  char *p;
  int len;
  int fd;
  int fildes;
  int i;

  if (path == NULL) {
    errno = EINVAL;
    return NULL;
  }

  for (len = 0; path[len]; len++)
    ;

  dirp = malloc(sizeof(DIR));
  if (dirp == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  /* room for the path, a separator, a name and the null */
  p = malloc(len + NAME_MAX + 2);
  if (p == NULL) {
    free(dirp);
    errno = ENOMEM;
    return NULL;
  }

  fd = _fdinit();
  if (fd == EOF) {
    free(p);
    free(dirp);
    return NULL;
  }
  fildes = _fdtable[fd];

  if (_oopendir(path, (unsigned char *) fildes) == EOF) {
    free((void *) fildes);
    _fdtable[fd] = EOF;
    free(p);
    free(dirp);
    /* O_OPENDIR fails for a file too, but O_OPEN opens a file */
    fd = open(path, O_RDONLY);
    if (fd != EOF) {
      close(fd);
      errno = ENOTDIR;
    } else {
      errno = ENOENT;
    }
    return NULL;
  }

  for (i = 0; i < len; i++)
    p[i] = path[i];
  if (len > 0 && p[len - 1] != '/')
    p[len++] = '/';
  p[len] = 0;

  dirp->dd_fd = fd;
  dirp->dd_eof = 0;
  dirp->dd_path = p;
  dirp->dd_plen = len;

  return dirp;
}
