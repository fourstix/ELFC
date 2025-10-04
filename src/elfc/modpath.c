#include <stdio.h>
#include <string.h>
#if defined(__linux__)
#include <unistd.h>
#elif defined(_WIN32)
#include <windows.h>
#endif
#include "modpath.h"

static void trim_filename_from_path(char *path) {
    char *last_slash = strrchr(path, '/');
    char *last_backslash = strrchr(path, '\\');

    // Determine which separator is the "last" one, considering both types
    char *last_separator = NULL;
    if (last_slash && last_backslash) {
        last_separator =
            (last_slash > last_backslash) ? last_slash : last_backslash;
    } else if (last_slash) {
        last_separator = last_slash;
    } else if (last_backslash) {
        last_separator = last_backslash;
    }

    if (last_separator != NULL) {
        // Keep the separator at the end.
        *++last_separator = '\0';
    }
}

void get_module_path(char *path_buf, size_t size) {
    if (path_buf == NULL) {
        return;
    }

    // If the path cannot be determined, an empty string is returned.
    *path_buf = '\0';

#if defined(__linux__)
    ssize_t len = readlink("/proc/self/exe", path_buf, size - 1);
    if (len != -1) {
        path_buf[len] = '\0';  // Null-terminate the string
        // Remove file name to get executable path.
        trim_filename_from_path(path_buf);
    } else {
        perror("readlink");
    }
#elif defined(_WIN32)
    if (GetModuleFileName(NULL, path_buf, size) != 0) {
        trim_filename_from_path(path_buf);
    } else {
        fprintf(stderr, "Error getting module file name.\n");
    }
#endif
}
