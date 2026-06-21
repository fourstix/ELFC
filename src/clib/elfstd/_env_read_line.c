/*
 * _env_read_line: read one line (up to '\n' or EOF) from fd into buf,
 * stripping the trailing newline, null-terminating the result.
 * Truncates lines longer than maxlen-1.
 * Returns: number of characters stored (0..maxlen-1), or -1 at EOF
 * with nothing read.
 */
#define _ELFCLIB_
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#pragma             extrn Cread

int _env_read_line(int fd, char *buf, int maxlen)
{
    int n;
    char c;
    int got;
    int r;

    n = 0;
    got = 0;

    for (;;) {
        r = read(fd, &c, 1);
        if (r <= 0) {
            /* EOF or error */
            if (got == 0 && n == 0)
                return -1;
            break;
        }
        got = 1;
        if (c == '\n')
            break;
        if (n < maxlen - 1) {
            buf[n] = c;
            n++;
        }
        /* else: silently truncate remainder of an over-long line */
    }

    buf[n] = '\0';
    return n;
}
