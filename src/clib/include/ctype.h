#ifndef _CTYPE_
#define _CTYPE_
 
/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif
 
 /* don't define all external functions inside C library procdures to prevent dupes */
#ifndef _ELFCLIB_
#pragma .link .library ctype.lib
#pragma .link .requires Cctype
#pragma #include include/ctype.inc
#endif

int	isalnum(int c);
int	isalpha(int c);
int	iscntrl(int c);
int	isdigit(int c);
int	isgraph(int c);
int	islower(int c);
int	isprint(int c);
int	ispunct(int c);
int	isspace(int c);
int	isupper(int c);
int	isxdigit(int c);
int	tolower(int c);
int	toupper(int c);

#endif
