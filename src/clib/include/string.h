#ifndef _STRING_
#define _STRING_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

#ifndef _ELFCLIB_
#pragma .link .library string.lib
#endif

#ifndef EOF
#define  EOF  (-1)
#endif

#ifndef NULL
#define  NULL (void*)0
#endif

void *memchr(const void *p, int c, size_t n);
int memcmp(const void *p1, const void *p2, size_t n);
void *memcpy(void *d, const void *s, size_t n);
void *memmove(void *d, const void *s, size_t n);
void *memset(void *p, int c, size_t n);
char *strcat(char *d, const char *a);
char *strchr(const char *s, int c);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *d, const char *s);
size_t strcspn(const char *s, const char *set);
char *strdup(const char *s);
char *strerror(int err);
size_t strlen(const char *s);
char *strncat(char *d, const char *a, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);
char *strncpy(char *d, const char *s, size_t n);
size_t strlcpy(char *dst, const char *src, size_t dsize);
char *strpbrk(const char *s, const char *set);
char *strrchr(const char *s, int c);
size_t strspn(const char *s, const char *set);
char *strstr(const char *s1, const char *s2);
char *strtok(char *s, const char *sep);

#endif
