/*
 * rename.c
 *
 * Replacement for the standard rename(), aware of the target's
 * lower-level same-folder rename primitive _rename().
 *
 * If old_path and new_path are in the same folder (i.e. everything
 * up to and including the last '/' is identical), this calls
 * _rename(old_path, new_name) directly, which is expected to be
 * cheap since it only needs to update a directory entry's name and
 * not move any file data.
 *
 * If the folders differ, the file must actually move between
 * directories: its contents are copied from old_path to new_path
 * using a small fixed-size buffer (so memory use does not depend on
 * file size), and old_path is then removed.
 *
 * Returns 0 on success, -1 on error.
 */
#define _ELFCLIB_
#include <stdio.h>

/* define only extern procedures required */
#pragma           extrn C_rename
#pragma           extrn Copen
#pragma           extrn Cclose
#pragma           extrn Cread
#pragma           extrn Cwrite
#pragma           extrn Cremove

#define RENAME_COPY_BUF  64

/*
 * find_dir_end: return a pointer one past the last '/' in path,
 * i.e. the start of the filename portion. If path contains no '/',
 * returns path itself (the whole string is the filename, folder is
 * implicitly the current/root directory).
 */
static const char *_find_dir_end(const char *path)
{
    const char *p;
    const char *last_slash;

    p = path;
    last_slash = NULL;
    while (*p != '\0') {
        if (*p == '/')
            last_slash = p;
        p++;
    }

    if (last_slash == NULL)
        return path;

    return last_slash + 1;
}

/*
 * same_folder: compare the directory portions of two paths
 * (the bytes up to, but not including, the filename start).
 * Returns 1 if identical, 0 otherwise.
 */
static int _same_folder(const char *old_path, const char *old_name,
                        const char *new_path, const char *new_name)
{
    int old_dir_len;
    int new_dir_len;
    int i;

    old_dir_len = (int)(old_name - old_path);
    new_dir_len = (int)(new_name - new_path);

    if (old_dir_len != new_dir_len)
        return 0;

    for (i = 0; i < old_dir_len; i++) {
        if (old_path[i] != new_path[i])
            return 0;
    }

    return 1;
}

/*
 * copy_and_remove: copy file contents from old_path to new_path
 * using a small fixed buffer, then remove old_path. Used when the
 * rename crosses folders and so cannot be done as a simple
 * directory-entry update.
 */
static int _copy_and_remove(const char *old_path, const char *new_path)
{
    int in_fd;
    int out_fd;
    int n;
    static char buf[RENAME_COPY_BUF];

    in_fd = open(old_path, O_RDONLY);
    if (in_fd < 0)
        return -1;

    out_fd = open(new_path, O_WRONLY | O_CREAT | O_TRUNC);
    if (out_fd < 0) {
        close(in_fd);
        return -1;
    }

    for (;;) {
        n = read(in_fd, buf, RENAME_COPY_BUF);
        if (n < 0) {
            close(in_fd);
            close(out_fd);
            return -1;
        }
        if (n == 0)
            break;               /* EOF */
        if (write(out_fd, buf, n) != n) {
            close(in_fd);
            close(out_fd);
            return -1;
        }
    }

    close(in_fd);
    close(out_fd);

    if (remove(old_path) != 0)
        return -1;

    return 0;
}

int rename(const char *old_path, const char *new_path)
{
    const char *old_name;
    const char *new_name;
    static char namebuf[64];
    int i;

    old_name = _find_dir_end(old_path);
    new_name = _find_dir_end(new_path);

    if (_same_folder(old_path, old_name, new_path, new_name)) {
        /* _rename takes non-const char* parameters; old_path is the
         * caller's string (not modified by _rename per its contract,
         * but the signature requires non-const), and the new name
         * must be copied into a local writable buffer. */
        i = 0;
        while (new_name[i] != '\0' && i < (int)sizeof(namebuf) - 1) {
            namebuf[i] = new_name[i];
            i++;
        }
        namebuf[i] = '\0';

        return _rename((char *)old_path, namebuf);
    }

    return _copy_and_remove(old_path, new_path);
}
