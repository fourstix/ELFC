#define _ELFCLIB_
#include <errno.h>

char *strerror(int err) {
	switch (err) {
	case EOK:	return "no error";
	case ENOENT:	return "no such file";
	case EACCESS:	return "access denied";
	case EIO:	return "input/output error";
	case ENFILE:	return "too many open files";
	case EINVAL:	return "invalid argument";
	case ENOMEM:	return "out of memory";
	case EBADF:  	return "bad file number";
	case EMFILE:	return "too many files open";
	default:	return "unknown error";
	}
}
