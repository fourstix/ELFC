#ifndef _STRING_
#define _STRING_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _ELFCLIB_
#pragma .link .library string.lib

#pragma             extrn Cmemchr
#pragma             extrn Cmemcmp
#pragma             extrn Cmemcpy
#pragma             extrn Cmemmove
#pragma             extrn Cmemset
#pragma             extrn Cstrcat
#pragma             extrn Cstrchr
#pragma             extrn Cstrcmp
#pragma             extrn Cstrcpy
#pragma             extrn Cstrcspn
#pragma             extrn Cstrdup
#pragma             extrn Cstrerror
#pragma             extrn Cstrlen
#pragma             extrn Cstrncat
#pragma             extrn Cstrncmp
#pragma             extrn Cstrncpy
#pragma             extrn Cstrlcpy
#pragma             extrn Cstrpbrk
#pragma             extrn Cstrrchr
#pragma             extrn Cstrspn
#pragma             extrn Cstrstr
#pragma             extrn Cstrtok
#endif

#ifndef EOF
#define  EOF  (-1)
#endif 

#ifndef NULL
#define  NULL (void*)0
#endif 

void *memchr(void *p, int c, int n);
int memcmp(void *p1, void *p2, int n);
void *memcpy(void *d, void *s, int n);
void *memmove(void *d, void *s, int n);
void *memset(void *p, int c, int n);
char *strcat(char *d, char *a);
char *strchr(char *s, int c);
int strcmp(char *s1, char *s2);
char *strcpy(char *d, char *s);
int strcspn(char *s, char *set);
char *strdup(char *s);
char *strerror(int err);
int strlen(char *s);
char *strncat(char *d, char *a, int n);
int strncmp(char *s1, char *s2, int n);
char *strncpy(char *d, char *s, int n);
char *strlcpy(char *d, char *s, int n);
char *strpbrk(char *s, char *set);
char *strrchr(char *s, int c);
int strspn(char *s, char *set);
char *strstr(char *s1, char *s2);
char *strtok(char *s, char *sep);

#endif
