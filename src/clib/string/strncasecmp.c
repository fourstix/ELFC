#define _ELFCLIB_
#include <string.h>
#include <ctype.h.>

#pragma             extrn Ctolower

#pragma .link .library ctype.lib

 int strncasecmp(const char *s1, const char *s2, size_t n) {
   const unsigned char *p1=(void *)s1, *p2=(void *)s2;

   if (!n--) return 0;

   for (; *p1 && *p2 && n && (*p1 == *p2 || tolower(*p1) == tolower(*p2)); p1++, p2++, n--);

   return tolower(*p1) - tolower(*p2);
 }
