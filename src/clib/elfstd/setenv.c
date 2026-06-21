/*
 * setenv.c
 *
 * Set (or update) an environment variable in the on-disk store.
 *
 * Strategy: stream the existing file (if any) into a new temporary
 * file, copying every line through unchanged except the one whose
 * name matches (which is replaced in place if overwrite is true, or
 * kept verbatim if overwrite is false), then append the new
 * NAME=VALUE line if no matching line was found. Finally the
 * temporary file replaces the original.
 *
 * This requires only a single fixed-size line buffer in memory,
 * regardless of how large the variable store grows.
 *
 * Returns 0 on success, -1 on error (matching the standard setenv).
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
#pragma             extrn Cstrlen
#pragma             extrn Cremove
#pragma             extrn Crename

int setenv(const char *name, const char *value, int overwrite)
{
    int in_fd;
    int out_fd;
    int len;
    static char line[ENV_LINE_MAX];
    static char namebuf[ENV_LINE_MAX];
    int found;
    char *val_part;
    const char *p;

    /* Reject names containing '=', as the real setenv does */
    p = name;
    while (*p != '\0') {
        if (*p == '=')
            return -1;
        p++;
    }

    found = 0;

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
                found = 1;
                if (overwrite) {
                    /* write the new value in this line's place */
                    write(out_fd, name, strlen(name));
                    write(out_fd, "=", 1);
                    write(out_fd, value, strlen(value));
                    write(out_fd, "\n", 1);
                } else {
                    /* keep the existing line verbatim */
                    write(out_fd, line, len);
                    write(out_fd, "\n", 1);
                }
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

    /* Variable did not exist in the file: append it */
    if (!found) {
        write(out_fd, name, strlen(name));
        write(out_fd, "=", 1);
        write(out_fd, value, strlen(value));
        write(out_fd, "\n", 1);
    }

    close(out_fd);

    /* Swap the temp file into place */
    remove(ENV_FILE_PATH);
    if (rename(ENV_TMP_PATH, ENV_FILE_PATH) != 0)
        return -1;

    return 0;
}
