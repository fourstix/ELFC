#ifndef _ASSERT_
#define _ASSERT_

/* include stdlib and stdio if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _STDIO_
#include <stdio.h>
#endif

#ifdef NDEBUG
#define assert(expr)
#else
#define assert(expr) if(!(expr)){\
 fprintf(stderr, "Assertion \'%s\' failed in file %s, line %d, function %s\n",\
 #expr, __FILE__, __LINE__, __FUNCTION__); abort();}
#endif

#endif
