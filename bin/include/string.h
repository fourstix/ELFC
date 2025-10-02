#ifndef _STRING_
#define _STRING_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _ELFCLIB_
#pragma .link .library string.lib
#pragma #include include/string.inc
#endif

#ifndef EOF
#define  EOF  (-1)
#endif 

#ifndef NULL
#define  NULL (void*)0
#endif 

void *memchr(void *p, int c, size_t n);
int memcmp(void *p1, void *p2, size_t n);
void *memcpy(void *d, void *s, size_t n);
void *memmove(void *d, void *s, size_t n);
void *memset(void *p, int c, size_t n);
char *strcat(char *d, char *a);
char *strchr(char *s, int c);
int strcmp(char *s1, char *s2);
char *strcpy(char *d, char *s);
size_t strcspn(char *s, char *set);
char *strdup(char *s);
char *strerror(int err);
size_t strlen(char *s);
char *strncat(char *d, char *a, size_t n);
int strncmp(char *s1, char *s2, size_t n);
char *strncpy(char *d, char *s, size_t n);
size_t strlcpy(char *d, char *s, size_t n);
char *strpbrk(char *s, char *set);
char *strrchr(char *s, int c);
size_t strspn(char *s, char *set);
char *strstr(char *s1, char *s2);
char *strtok(char *s, char *sep);

#endif
