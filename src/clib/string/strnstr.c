#define _ELFCLIB_
#include <string.h>

#pragma           extrn Cstrncmp
#pragma           extrn Cstrlen
/*
 * Find the first occurrence of a string s2 in s1, where the search is limited to the
 * first n characters of s1.
 */

char *strnstr(const char *s1, const char *s2, size_t n) {
	char c, sc;
	size_t len;

	if ((c = *s2++) != '\0') {
		len = strlen(s2);
		do {
			do {
				if (n-- < 1 || (sc = *s1++) == '\0')
					return (NULL);
			} while (sc != c);
			if (len > n)
				return (NULL);
		} while (strncmp(s1, s2, len) != 0);
		s1--;
	}
	return ((char *)s1);
}
