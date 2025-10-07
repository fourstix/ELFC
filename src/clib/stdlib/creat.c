#define _ELFCLIB_
#include <stdlib.h>

#pragma             extrn Copen

int	 creat(char *path, int mode) {
  /* make sure create and truncate flags are set */
  mode |= O_CREAT;
  mode |= O_TRUNC;
  /* and pass to the open function */    
  return open(path, mode);
}
