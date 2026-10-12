#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "edos.h"

#pragma             extrn Cerrno
#pragma             extrn C_fdtable
#pragma             extrn Cmalloc

/*
 *  ELF-DOS File Descriptor Layout
 * --------------------------------
 *  Byte : Description       : Length
 * --------------------------------
 *  0-31 : File Control Block:  32
 * --------------------------------
 *      Sector Buffer (512 Bytes)
 * --------------------------------
 *   Total FD size = 544 bytes
 *
 *  The File Control Block belongs to the kernel and its layout is not
 *  used here.  The kernel requires that it does not cross a 256-byte
 *  page boundary, so it is placed on a 32-byte boundary.  The two bytes
 *  before it hold the address of the memory block it was taken from.
 */

int _fdinit(void) {
  int fildes;
  int fd;
  int block;

  /* find available entry in table, skipping over the */
  /* predefined entries for stdin, stdout & stderr */
  for(fd = FD_SYS; fd < FD_MAX; fd++) {
    if(EOF == _fdtable[fd])
      break;
  }


  /* if no more system entries are available, exit with error */
  if (fd >= FD_MAX) {
      errno = EMFILE;
      return EOF;
  }


  block = (int) malloc(_FCB_ALLOC);

  /* if malloc failed return error */
  if (block == 0) {
    errno = ENOMEM;
    return EOF;
  }

  /* align the fcb, leaving room below it for the block address */
  fildes = (block + 33) & 0xFFE0;
  _FCB_BLOCK(fildes) = block;

  /* set the system file descriptor for the new entry */
  _fdtable[fd] = fildes;

  return fd;
}
