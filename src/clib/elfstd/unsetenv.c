/*
 * unsetenv.c
 *
 * Remove an environment variable from the on-disk store.
 *
 * Strategy: stream the existing file into a new temporary file,
 * copying every line through unchanged except the one whose name
 * matches (which is simply dropped), then the temporary file
 * replaces the original.
 *
 * Memory use is a single fixed-size line buffer, regardless of how
 * large the variable store is.
 *
 * Returns 0 on success (including when the variable was not set to
 * begin with, matching the standard unsetenv), -1 on error.
 */
#define _ELFCLIB_
#include <stdlib.h>
#include <string.h>

#pragma             extrn Copen
#pragma             extrn C_env_read_line
#pragma             extrn C_env_split_line
#pragma             extrn Cwrite
#pragma             extrn Cclose
#pragma             extrn Cstrcpy
#pragma             extrn Cstrcmp
#pragma             extrn Cremove
#pragma             extrn Crename

int unsetenv(const char *name)
{
    int in_fd;
    int out_fd;
    int len;
    static char line[ENV_LINE_MAX];
    static char namebuf[ENV_LINE_MAX];
    char *val_part;
    const char *p;

    /* Reject names containing '=', as the real unsetenv does */
    p = name;
    while (*p != '\0') {
        if (*p == '=')
            return -1;
        p++;
    }

    out_fd = open(ENV_TMP_PATH, O_WRONLY | O_CREAT | O_TRUNC);
    if (out_fd < 0)
        return -1;

    in_fd = open(ENV_FILE_PATH, O_RDONLY);
    if (in_fd >= 0) {
        for (;;) {
            len = _env_read_line(in_fd, line, ENV_LINE_MAX);
            if (len < 0)
                break;            /* EOF */

            /* Keep a copy of the name portion for comparison, since
             * split_line modifies the buffer in place. */
            strcpy(namebuf, line);
            val_part = _env_split_line(namebuf);

            if (val_part != NULL && strcmp(namebuf, name) == 0) {
                /* matching line: drop it */
                continue;
            }

            /* unrelated line: copy through unchanged */
            if (len > 0) {
                write(out_fd, line, len);
                write(out_fd, "\n", 1);
            }
        }
        close(in_fd);
    }

    close(out_fd);

    /* Swap the temp file into place */
    remove(ENV_FILE_PATH);
    if (rename(ENV_TMP_PATH, ENV_FILE_PATH) != 0)
        return -1;

    return 0;
}
