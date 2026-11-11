#define _ELFCLIB_
#include <errno.h>

char *strerror(int err) {
	switch (err) {
	case EOK:	    return "no error";
	case ENOENT:	return "no such file";
	case EIO:	    return "input/output error";
	case EBADF:  	return "bad file number";
#ifdef ENOTDIR
	case ENOTDIR:	return "not a directory";
#endif
	case ENOMEM:	return "out of memory";
	case EACCES:	return "file access error";
	case EINVAL:	return "invalid argument";
	case ENFILE:	return "too many open files";
	case EMFILE:	return "out of file handles";
	case EDOM:    return "argument out of domain";
  case ERANGE:  return "result out of range";
	default:	    return "unknown error";
	}
}
