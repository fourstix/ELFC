#ifndef _KDIR_
#define _KDIR_

/*
 * Private kernel interface for the ELF-DOS dirent library.  The register
 * save and result macros are shared with the edosstd library.
 */
#include "../edosstd/edos.h"

/* select the ELF-DOS DIR in dirent.h, the library is built without -E */
#define _DIRENT_EDOS_
#include <dirent.h>

/* offsets of the big-endian fields in the kernel's directory entry */
#define _KD_ATTR    128
#define _KD_CLUST   129
#define _KD_SIZE    131
#define _KD_TIME    135
#define _KD_DATE    137

int  _kpathres(char *path, unsigned int *clust, char **name, int *drive);
int  _kstat(char *path, char *buf);
void _kdiropen(unsigned int clust);
int  _kdirread(char *buf);
void _kdirsave(char *state);
int  _kdirrestore(char *state);

#endif
