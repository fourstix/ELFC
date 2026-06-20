/*
 * _split_line: given a "NAME=VALUE" line, locate the '=' separator.
 * Returns a pointer to the VALUE portion (after '='), or NULL if
 * no '=' is present. Replaces '=' with '\0' in place, so the NAME
 * portion becomes a separate null-terminated string at the start
 * of the buffer.
 */
#define _ELFCLIB_
#include <stdlib.h>

char *_env_split_line(char *line)
{
    char *p;

    p = line;
    while (*p != '\0') {
        if (*p == '=') {
            *p = '\0';
            return p + 1;
        }
        p++;
    }
    return NULL;
}
