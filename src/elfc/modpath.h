#ifndef MOD_PATH_H
#define MOD_PATH_H

#include <stddef.h>

#if defined(__linux__)
#include <linux/limits.h>
#define MAXPATH     PATH_MAX
#elif defined(_WIN32)
#define MAXPATH     MAX_PATH
#endif

extern void get_module_path(char *path_buf, size_t size);

#endif  // MOD_PATH_H