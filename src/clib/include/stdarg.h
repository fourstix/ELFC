#ifndef _STDARG_
#define _STDARG_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

/* Arguments on the stack are all int sized */
typedef int* va_list;

/* Set argument pointer to next argument after last */
#define va_start(ap, last)  ((ap) = ((int*)(&last) + 1))

/* Get next argument from stack and cast to type T */
#define va_arg(ap, T) (T)(*ap++)

/* Set argument poiter to null */
#define va_end(ap)  (ap = (void*)0)

#endif
