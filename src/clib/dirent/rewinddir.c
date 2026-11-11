#define _ELFCLIB_
#include <stdlib.h>
#include "odir.h"

#pragma             extrn Clseek

/* Start reading an open directory again from its first entry */
void rewinddir(DIR *dirp) {
  if (dirp != NULL) {
    lseek(dirp->dd_fd, 0, SEEK_SET);
    dirp->dd_eof = 0;
  }
}
