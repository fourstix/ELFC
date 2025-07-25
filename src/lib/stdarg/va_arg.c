#define _ELFCLIB_
#include <stdarg.h>

/* Extract vararg, advance pointer */

void *va_arg(void **ap) {
	return *((void **) *ap)++;
}
