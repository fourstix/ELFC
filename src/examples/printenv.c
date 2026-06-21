/*
 * printenv.c
 *
 * Mimics the Linux printenv command:
 *   printenv            -- list every NAME=VALUE pair, one per line
 *   printenv NAME...    -- print the value of each named variable
 *                           (one per line, in the order given; a
 *                           variable that is not set prints nothing
 *                           for that argument, matching GNU printenv)
 *
 * Streams the store file directly to the console using the same
 * small fixed-size line buffer as getenv/setenv; no dynamic
 * allocation and no requirement to hold the whole file in memory.
 *
 * Uses the platform's puts() (writes a string followed by a newline)
 * rather than a raw write() to file descriptor 1, since the target
 * console is not addressed that way.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_all(void)
{
    int fd;
    static char line[ENV_LINE_MAX];
    int len;

    fd = open(ENV_FILE_PATH, O_RDONLY);
    if (fd < 0)
        return;                  /* no file: nothing to print */

    for (;;) {
        len = _env_read_line(fd, line, ENV_LINE_MAX);
        if (len < 0)
            break;
        if (len == 0)
            continue;
        puts(line);
    }

    close(fd);
}

static void print_one(const char *name)
{
    char *value;

    value = getenv(name);
    if (value != NULL)
        puts(value);
}

int main(int argc, char *argv[])
{
    int i;

    if (argc <= 1) {
        print_all();
        return 0;
    }

    for (i = 1; i < argc; i++)
        print_one(argv[i]);

    return 0;
}
