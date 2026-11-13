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
 * may be done between calls to readdir.  Entries may be read ahead, so
 * a file added or removed after opendir or rewinddir may or may not
 * be returned, as POSIX allows.
 *
 * Elf/OS
 *   "" names the current directory and "/" the root directory.
 *   Elf/OS directories have no "." or ".." entries.  An open
 *   directory uses one of the C library's file descriptors.
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

//grw - added tests for directory entry file types
#define DE_ISRDONLY(e)   ((e)->d_attr & _A_RDONLY)
#define DE_ISHIDDEN(e)   ((e)->d_attr & _A_HIDDEN)
#define DE_ISSYSTEM(e)   ((e)->d_attr & _A_SYSTEM)
#define DE_ISARCH(e)     ((e)->d_attr & _A_ARCH)
#define DE_ISEXEC(e)     ((e)->d_attr & _A_EXEC)
/* normal file type has no bits set so test equal to zero */
#define DE_ISNORMAL(e)   ((e)->d_attr == _A_NORMAL)


#ifdef _DIRENT_EDOS_

/* sizes of the kernel's directory entry and scan snapshot buffers */
#define _DIRENT_LEN     139
#define _DIRSTATE_LEN   9

/* most entries read ahead at a time, fewer if memory is short */
#define _DIRSLOTS       8

/*
 * An open ELF-DOS directory.  The fields are private to the library.
 *
 * The kernel has one directory scan, so each DIR keeps a snapshot of
 * its position and restores it before reading, which reads the
 * directory sector again.  To restore less often, readdir reads up to
 * dd_nslots entries at a time into dd_slot and returns them in turn.
 * The kernel's 139 byte entry is read into a slot and converted in
 * place to a struct dirent.
 *
 *   dd_clust   first cluster of the directory, 0 for a root directory
 *   dd_loc     nonzero once the scan is started
 *   dd_eof     set once the kernel reaches the end of the directory
 *   dd_n       number of entries in dd_slot
 *   dd_i       next entry in dd_slot to return
 *   dd_nslots  number of entries dd_slot has room for
 *   dd_root    "X:/" for the directory's drive, used to select it
 *   dd_state   the kernel's scan position after the last entry read
 *   dd_slot    entries read ahead, dd_nslots are allocated
 */
typedef struct {
  unsigned int  dd_clust;
  unsigned int  dd_loc;
  int           dd_eof;
  int           dd_n;
  int           dd_i;
  int           dd_nslots;
  char          dd_root[4];
  char          dd_state[_DIRSTATE_LEN + 1];
  struct dirent dd_slot[1];
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
 *   dd_path    copy of the path, to open the directory again
 *   dd_raw     the directory entry as it was read
 */
typedef struct {
  struct dirent dd_ent;
  int           dd_fd;
  int           dd_eof;
  char         *dd_path;
  unsigned char dd_raw[_DIRENT_LEN];
} DIR;

#endif

DIR *opendir(const char *path);
struct dirent *readdir(DIR *dirp);
void rewinddir(DIR *dirp);
int closedir(DIR *dirp);

#endif
