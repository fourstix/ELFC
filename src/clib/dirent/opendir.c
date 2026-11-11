#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "odir.h"

#pragma             extrn Cerrno
#pragma             extrn Cmalloc
#pragma             extrn Cfree
#pragma             extrn Copen
#pragma             extrn Cclose
#pragma             extrn C_odiropen

/*
 * Open a directory for reading.  Returns NULL and sets errno to
 * ENOENT when the path is not found, ENOTDIR when it names a file,
 * ENOMEM when there is no memory, EMFILE when there is no free file
 * descriptor, or EINVAL for NULL.
 *
 * The directory is opened as a file with O_OPENDIR, in a file
 * descriptor from the C library's table, and read with read().
 */
DIR *opendir(const char *path) {
  DIR *dirp;
  char *p;
  int len;
  int fd;
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

  /* a copy of the path, to open the directory again in rewinddir */
  p = malloc(len + 1);
  if (p == NULL) {
    free(dirp);
    errno = ENOMEM;
    return NULL;
  }

  errno = EOK;
  fd = _odiropen(path);
  if (fd == EOF) {
    free(p);
    free(dirp);
    /* errno is set when there was no free file descriptor */
    if (errno != EOK)
      return NULL;
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

  for (i = 0; i <= len; i++)
    p[i] = path[i];

  dirp->dd_fd = fd;
  dirp->dd_eof = 0;
  dirp->dd_path = p;

  return dirp;
}
