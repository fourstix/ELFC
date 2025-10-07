#define _ELFCLIB_
#include <stdarg.h>

/* Expect address of last known argument, return vararg pointer */

void **va_start(void *last) {
	return (void **) last + 1;
}
