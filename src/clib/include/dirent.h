#ifndef _DIRENT_
#define _DIRENT_

/*
 * dirent.h -- directory listing for Elf/OS and ELF-DOS programs
 *
 *   DIR *opendir(const char *path);
 *   struct dirent *readdir(DIR *dirp);
 *   void rewinddir(DIR *dirp);
 *   int closedir(DIR *dirp);
 *
 * An Elf/OS program links dirent.lib, an ELF-DOS program (elfc -E)
 * links edosdir.lib.  Both fill in the same struct dirent fields, and
 * the attribute bits and DE_ macros below work the same on both.
 *
 * readdir returns every entry, including hidden files.  Any number of
 * directories may be open at the same time, and other file operations
 * may be done between calls to readdir.
 *
 * Elf/OS
 *   "" names the current directory and "/" the root directory.
 *   Elf/OS directories have no "." or ".." entries.  The file size
 *   is not kept in an Elf/OS directory entry, so readdir opens each
 *   file to find it, which needs a free file descriptor.
 *
 * ELF-DOS
 *   The path may start with a drive letter ("D:/games") and may be
 *   relative to that drive's current directory.  "", "C:" and "." all
 *   name a current directory, "/" and "C:/" name a root directory.
 *   A subdirectory has "." and ".." entries, the root has none.
 */

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

/* an ELF-DOS program, or the ELF-DOS library, which is built without -E */
#ifdef __ELFDOS__
#define _DIRENT_EDOS_
#endif

/* don't define all external functions inside C library procedures to prevent dupes */
#ifndef _ELFCLIB_
#ifdef _DIRENT_EDOS_
#pragma .link .library edosdir.lib
#else
#pragma .link .library dirent.lib
#endif
#endif

/* in case errno.h is older than this library */
#ifndef ENOTDIR
#define ENOTDIR     20
#endif

/* longest name the system returns, not counting the null */
#ifdef _DIRENT_EDOS_
#define NAME_MAX    127
#else
#define NAME_MAX    19
#endif

/*
 * Attribute bits in d_attr.  These are the FAT bits, which ELF-DOS
 * returns as they are.  Elf/OS flags are changed to the same bits,
 * and the Elf/OS executable flag is returned as _A_EXEC.
 */
#define _A_NORMAL   0x00
#define _A_RDONLY   0x01
#define _A_HIDDEN   0x02
#define _A_SYSTEM   0x04
#define _A_SUBDIR   0x10
#define _A_ARCH     0x20
#define _A_EXEC     0x80

/*
 * A directory entry.
 *
 *   d_name    null-terminated file name (ELF-DOS long name if any)
 *   d_attr    attribute bits, see _A_SUBDIR and the others above
 *   d_ino     first cluster or allocation unit of the file
 *   d_size    file size in bytes, as a 32-bit uint32_t {low, high},
 *             0 for a directory on Elf/OS
 *   d_time    last-write time, packed, see DE_HOUR below
 *   d_date    last-write date, packed, see DE_YEAR below
 */
struct dirent {
  char          d_name[NAME_MAX + 1];
  unsigned char d_attr;
  unsigned int  d_ino;
  struct _dword d_size;
  unsigned int  d_time;
  unsigned int  d_date;
};

/*
 * Macros to examine a struct dirent pointer.  Both systems pack the
 * date and time the same way, but count years from a different base.
 */
#ifdef _DIRENT_EDOS_
#define _DE_EPOCH     1980
#else
#define _DE_EPOCH     1972
#endif

#define DE_ISDIR(e)   ((e)->d_attr & _A_SUBDIR)
#define DE_YEAR(e)    (((e)->d_date >> 9) + _DE_EPOCH)
#define DE_MONTH(e)   (((e)->d_date >> 5) & 0x0F)
#define DE_DAY(e)     ((e)->d_date & 0x1F)
#define DE_HOUR(e)    ((e)->d_time >> 11)
#define DE_MIN(e)     (((e)->d_time >> 5) & 0x3F)
#define DE_SEC(e)     (((e)->d_time & 0x1F) << 1)

#ifdef _DIRENT_EDOS_

/* sizes of the kernel's directory entry and scan snapshot buffers */
#define _DIRENT_LEN     139
#define _DIRSTATE_LEN   9

/*
 * An open ELF-DOS directory.  The fields are private to the library.
 * The kernel's 139 byte entry is read into dd_ent and converted in place.
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

#else

/* size of an Elf/OS directory entry */
#define _DIRENT_LEN     32

/*
 * An open Elf/OS directory.  The fields are private to the library.
 *
 *   dd_ent     the entry readdir returns
 *   dd_fd      file descriptor of the directory, opened with O_OPENDIR
 *   dd_eof     set once the end of the directory is reached
 *   dd_path    the path with a separator, with room to add a name
 *   dd_olen    length of the path as it was given to opendir
 *   dd_plen    length of the path in dd_path, with the separator
 *   dd_raw     the directory entry as it was read
 */
typedef struct {
  struct dirent dd_ent;
  int           dd_fd;
  int           dd_eof;
  char         *dd_path;
  int           dd_olen;
  int           dd_plen;
  unsigned char dd_raw[_DIRENT_LEN];
} DIR;

#endif

DIR *opendir(const char *path);
struct dirent *readdir(DIR *dirp);
void rewinddir(DIR *dirp);
int closedir(DIR *dirp);

#endif
