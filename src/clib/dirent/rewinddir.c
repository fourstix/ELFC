#define _ELFCLIB_
#include <stdlib.h>
#include "odir.h"

#pragma             extrn Cclose
#pragma             extrn C_odiropen

/*
 * Start reading an open directory again from its first entry.
 *
 * The directory is closed and opened again, rather than moved to its
 * start with lseek.  An Elf/OS seek reads the file's own directory
 * entry again, from where it was found when it was opened, but the
 * current and root directories are opened from kernel copies of their
 * entries, so a seek would start them from the wrong place.  If the
 * directory cannot be opened again, readdir returns NULL.
 */
void rewinddir(DIR *dirp) {
  char c;

  if (dirp == NULL)
    return;

  if (dirp->dd_fd != EOF)
    close(dirp->dd_fd);

  /* open the path as it was given, without the added separator */
  c = dirp->dd_path[dirp->dd_olen];
  dirp->dd_path[dirp->dd_olen] = 0;
  dirp->dd_fd = _odiropen(dirp->dd_path);
  dirp->dd_path[dirp->dd_olen] = c;

  dirp->dd_eof = (dirp->dd_fd == EOF);
}
