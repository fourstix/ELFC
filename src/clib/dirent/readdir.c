#define _ELFCLIB_
#include <stdlib.h>
#include <errno.h>
#include "odir.h"

#pragma             extrn Cerrno
#pragma             extrn Cread
#pragma             extrn Copen
#pragma             extrn Cclose
#pragma             extrn Clseek32

/*
 * Return the next entry of an open directory, or NULL at the end of
 * the directory.  errno is set to EBADF for a NULL DIR, or by read()
 * if the directory cannot be read; it is left unchanged at the end
 * of the directory.  The entry is overwritten by the next readdir on
 * the same DIR.
 *
 * An Elf/OS directory is a file of 32 byte entries, and an entry with
 * no starting allocation unit is unused.  The entry holds only the
 * number of bytes in the file's last allocation unit, so the size of
 * a file is found by opening it and seeking to its end.
 */
struct dirent *readdir(DIR *dirp) {
  struct dirent *de;
  unsigned char *raw;
  unsigned char flags;
  struct _dword zero;
  char *name;
  int fd;
  int i;

  if (dirp == NULL) {
    errno = EBADF;
    return NULL;
  }

  if (dirp->dd_eof)
    return NULL;

  raw = dirp->dd_raw;
  for (;;) {
    if (read(dirp->dd_fd, raw, _DIRENT_LEN) != _DIRENT_LEN) {
      dirp->dd_eof = 1;
      return NULL;
    }
    if (raw[_OD_AU] | raw[_OD_AU + 1] | raw[_OD_AU + 2] | raw[_OD_AU + 3])
      break;
  }

  de = &dirp->dd_ent;

  for (i = 0; i < NAME_MAX && raw[_OD_NAME + i]; i++)
    de->d_name[i] = raw[_OD_NAME + i];
  de->d_name[i] = 0;

  flags = raw[_OD_FLAGS];
  de->d_attr = _A_NORMAL;
  if (flags & _OF_DIR)     de->d_attr |= _A_SUBDIR;
  if (flags & _OF_EXEC)    de->d_attr |= _A_EXEC;
  if (flags & _OF_WRPROT)  de->d_attr |= _A_RDONLY;
  if (flags & _OF_HIDDEN)  de->d_attr |= _A_HIDDEN;
  if (flags & _OF_ARCHIVE) de->d_attr |= _A_ARCH;

  de->d_ino  = (raw[_OD_AU + 2] << 8) | raw[_OD_AU + 3];
  de->d_date = (raw[_OD_DATE] << 8) | raw[_OD_DATE + 1];
  de->d_time = (raw[_OD_TIME] << 8) | raw[_OD_TIME + 1];

  de->d_size.low = 0;
  de->d_size.high = 0;

  if (!(flags & _OF_DIR)) {
    /* add the name to the path, open the file and seek to its end */
    name = dirp->dd_path + dirp->dd_plen;
    for (i = 0; de->d_name[i]; i++)
      name[i] = de->d_name[i];
    name[i] = 0;

    fd = open(dirp->dd_path, O_RDONLY);
    if (fd != EOF) {
      zero.low = 0;
      zero.high = 0;
      de->d_size = lseek32(fd, zero, SEEK_END);
      if (de->d_size.low == 0xFFFF && de->d_size.high == 0xFFFF) {
        de->d_size.low = 0;
        de->d_size.high = 0;
      }
      close(fd);
    }

    name[0] = 0;
  }

  return de;
}
