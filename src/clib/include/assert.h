#ifndef _ASSERT_
#define _ASSERT_
  
/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif
  
/* don't define all external functions inside C libraries to prevent dupes */
#ifndef _ELFCLIB_ 
#pragma .link .library assert.lib
#pragma             extrn Cassert  
#endif

#ifdef NDEBUG
#pragma #define NDEBUG
#endif

void assert(int a, char *file, int line);

#endif
