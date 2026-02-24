#ifndef _ERRNO_
#define _ERRNO_

extern int errno;

/*
 * Macros and values as defined by Posix standard
 * See: https://en.wikipedia.org/wiki/Errno.h
 */

#define EOK     0
#define ENOENT  2
#define EIO     5
#define EBADF   9
#define ENOMEM  12
#define EACCES  13
#define EINVAL  22
#define ENFILE  23
#define EMFILE  24
#define ERANGE  34

#endif
