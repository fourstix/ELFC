#ifndef _STDARG_
#define _STDARG_
 
/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif
 
#ifndef _ELFCLIB_
#pragma .link .library stdarg.lib 
#pragma             extrn Cva_start
#pragma             extrn Cva_arg
#pragma             extrn Cva_end
#endif


typedef void** va_list;
/*
 * These are (slightly incompatible) functions,
 * because we don't have parameterized macros.
 */

void	**va_start(void *last);
void	 *va_arg(void **ap);
void	  va_end(void **ap);

#endif
