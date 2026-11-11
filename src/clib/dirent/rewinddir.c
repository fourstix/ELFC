#define _ELFCLIB_
#include <stdlib.h>
#include <dirent.h>

/* Start reading an open directory again from its first entry */
void rewinddir(DIR *dirp) {
  if (dirp != NULL) {
    dirp->dd_loc = 0;
    dirp->dd_eof = 0;
  }
}
