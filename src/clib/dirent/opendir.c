#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include "kdir.h"

#pragma             extrn Cerrno
#pragma             extrn Cmalloc
#pragma             extrn Cfree
#pragma             extrn C_kpathres
#pragma             extrn C_kstat

/*
 * Open a directory for reading.  Returns NULL and sets errno to
 * ENOENT when the path is not found, ENOTDIR when it names a file,
 * ENOMEM when there is no memory for the DIR, or EINVAL for NULL.
 *
 * K_PATH_RESOLVE finds the parent directory and the final path
 * component, which is looked up with K_STAT unless it already names
 * a directory: empty (a path ending in a separator, or a bare drive),
 * "." or the ".." of a root directory, which has no "." or ".."
 * entries of its own.
 */
DIR *opendir(const char *path) {
  DIR *dirp;
  unsigned char *ent;
  char *name;
  unsigned int clust;
  int drive;

  if (path == NULL) {
    errno = EINVAL;
    return NULL;
  }

  dirp = malloc(sizeof(DIR));
  if (dirp == NULL) {
    errno = ENOMEM;
    return NULL;
  }

  if (_kpathres(path, &clust, &name, &drive) == EOF) {
    free(dirp);
    errno = ENOENT;
    return NULL;
  }

  /* anything but "", "." or a root's ".." must be a directory entry */
  if (!(name[0] == 0
        || (name[0] == '.' && name[1] == 0)
        || (name[0] == '.' && name[1] == '.' && name[2] == 0 && clust == 0))) {
    ent = (unsigned char *) &dirp->dd_ent;
    if (_kstat(path, ent) == EOF) {
      free(dirp);
      errno = ENOENT;
      return NULL;
    }
    if (!(ent[_KD_ATTR] & _A_SUBDIR)) {
      free(dirp);
      errno = ENOTDIR;
      return NULL;
    }
    clust = (ent[_KD_CLUST] << 8) | ent[_KD_CLUST + 1];
  }

  dirp->dd_clust = clust;
  dirp->dd_loc = 0;
  dirp->dd_eof = 0;
  dirp->dd_root[0] = 'C' + drive;
  dirp->dd_root[1] = ':';
  dirp->dd_root[2] = '/';
  dirp->dd_root[3] = 0;

  return dirp;
}
