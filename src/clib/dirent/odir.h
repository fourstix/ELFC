#ifndef _ODIR_
#define _ODIR_

/*
 * Private Elf/OS interface for the dirent library.  It uses the
 * dirent.h in this source tree, which may be newer than the installed
 * one.
 */
#include "../include/dirent.h"

/*
 * Offsets of the big-endian fields in an Elf/OS directory entry
 *
 *   _OD_AU      starting allocation unit, 4 bytes, 0 for an unused entry
 *   _OD_EOF     bytes used in the last allocation unit, 2 bytes
 *   _OD_FLAGS   flags, see _OF_DIR and the others below
 *   _OD_DATE    date, 2 bytes
 *   _OD_TIME    time, 2 bytes
 *   _OD_NAME    null-terminated name, 20 bytes
 */
#define _OD_AU      0
#define _OD_EOF     4
#define _OD_FLAGS   6
#define _OD_DATE    7
#define _OD_TIME    9
#define _OD_NAME    12

/* Elf/OS directory entry flags */
#define _OF_DIR     0x01
#define _OF_EXEC    0x02
#define _OF_WRPROT  0x04
#define _OF_HIDDEN  0x08
#define _OF_ARCHIVE 0x10

/* offsets in a file descriptor, and the DTA size */
#define _FD_DTA     4
#define _FD_DIRSEC  9
#define _FD_DTALEN  512

int _oopendir(char *path, unsigned char *fildes);
int _odiropen(char *path);
unsigned int _olumps(unsigned int lump, int drive);

#endif
