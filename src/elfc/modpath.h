#ifndef MOD_PATH_H
#define MOD_PATH_H

#include <stddef.h>

#ifdef __linux__
#include <linux/limits.h>
#define MAXPATH     PATH_MAX
#else
#ifdef _WIN32
#define MAXPATH     240
#else
#define MAXPATH     128
#endif
#endif


extern void get_module_path(char *path_buf, size_t size);

#endif  // MOD_PATH_H
