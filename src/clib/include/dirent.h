#ifndef _DIRENT_
#define _DIRENT_

/*
 * dirent.h -- directory listing for ELF-DOS programs (elfc -E)
 *
 *   DIR *opendir(const char *path);
 *   struct dirent *readdir(DIR *dirp);
 *   void rewinddir(DIR *dirp);
 *   int closedir(DIR *dirp);
 *
 * The path may start with a drive letter ("D:/games") and may be
 * relative to that drive's current directory.  "", "C:" and "." all
 * name a current directory, "/" and "C:/" name a root directory.
 *
 * readdir returns every entry the kernel reports, including hidden
 * files and the "." and ".." entries of a subdirectory.  The root
 * directory has no "." or ".." entries.  Volume labels are never
 * returned.
 *
 * Any number of directories may be open at the same time, and other
 * file operations may be done between calls to readdir.
 */

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

/* don't define all external functions inside C library procedures to prevent dupes */
#ifndef _ELFCLIB_
#pragma .link .library dirent.lib
#endif

/* in case errno.h is older than this library */
#ifndef ENOTDIR
#define ENOTDIR     20
#endif

/* longest name the kernel returns, not counting the null */
#define NAME_MAX    127

/* FAT attribute bits in d_attr */
#define _A_NORMAL   0x00
#define _A_RDONLY   0x01
#define _A_HIDDEN   0x02
#define _A_SYSTEM   0x04
#define _A_SUBDIR   0x10
#define _A_ARCH     0x20

/*
 * A directory entry.  The kernel returns its entry in big-endian
 * fields, which readdir converts in place to these fields.
 *
 *   d_name    null-terminated file name, long name when there is one
 *   d_attr    FAT attribute bits, see _A_SUBDIR and the others above
 *   d_ino     first cluster of the file (0 for an empty file)
 *   d_size    file size in bytes, as a 32-bit uint32_t {low, high}
 *   d_time    last-write time, packed FAT format, see DE_HOUR below
 *   d_date    last-write date, packed FAT format, see DE_YEAR below
 */
struct dirent {
  char          d_name[NAME_MAX + 1];
  unsigned char d_attr;
  unsigned int  d_ino;
  struct _dword d_size;
  unsigned int  d_time;
  unsigned int  d_date;
};

/* Macros to examine a struct dirent pointer */
#define DE_ISDIR(e)   ((e)->d_attr & _A_SUBDIR)
#define DE_YEAR(e)    (((e)->d_date >> 9) + 1980)
#define DE_MONTH(e)   (((e)->d_date >> 5) & 0x0F)
#define DE_DAY(e)     ((e)->d_date & 0x1F)
#define DE_HOUR(e)    ((e)->d_time >> 11)
#define DE_MIN(e)     (((e)->d_time >> 5) & 0x3F)
#define DE_SEC(e)     (((e)->d_time & 0x1F) << 1)

/* sizes of the kernel's directory entry and scan snapshot buffers */
#define _DIRENT_LEN     139
#define _DIRSTATE_LEN   9

/*
 * An open directory.  The fields are private to the library.
 *
 *   dd_ent     the entry readdir returns, also the kernel's buffer
 *   dd_clust   first cluster of the directory, 0 for a root directory
 *   dd_loc     entries read so far, 0 means the scan is not started
 *   dd_eof     set once the end of the directory is reached
 *   dd_root    "X:/" for the directory's drive, used to select it
 *   dd_state   the kernel's scan position after the last readdir
 */
typedef struct {
  struct dirent dd_ent;
  unsigned int  dd_clust;
  unsigned int  dd_loc;
  int           dd_eof;
  char          dd_root[4];
  char          dd_state[_DIRSTATE_LEN + 1];
} DIR;

DIR *opendir(const char *path);
struct dirent *readdir(DIR *dirp);
void rewinddir(DIR *dirp);
int closedir(DIR *dirp);

#endif
