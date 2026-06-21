/*
 * getenv.c
 *
 * Look up an environment variable's value in the on-disk store.
 *
 * Like the standard C library, returns a pointer to an internal
 * static buffer that remains valid until the next call to getenv
 * (and is also overwritten by setenv's internal scanning, so the
 * value should be copied out by the caller if it must persist
 * across a subsequent setenv call).
 *
 * Memory use: one fixed-size line buffer; no dynamic allocation.
 */
#define _ELFCLIB_
#include <stdlib.h>
#include <string.h>

#pragma             extrn Copen
#pragma             extrn Cclose
#pragma             extrn C_env_read_line
#pragma             extrn C_env_split_line
#pragma             extrn Cstrcmp

char *getenv(const char *name)
{
    static char line[ENV_LINE_MAX];
    int fd;
    int len;
    char *value;

    fd = open(ENV_FILE_PATH, O_RDONLY);
    if (fd < 0)
        return NULL;            /* no env file yet: nothing is set */

    for (;;) {
        len = _env_read_line(fd, line, ENV_LINE_MAX);
        if (len < 0)
            break;               /* EOF */
        if (len == 0)
            continue;            /* blank line */

        value = _env_split_line(line);
        if (value == NULL)
            continue;            /* malformed line, skip */

        if (strcmp(line, name) == 0) {
            close(fd);
            return value;
        }
    }

    close(fd);
    return NULL;
}
