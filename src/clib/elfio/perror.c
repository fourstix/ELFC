/*
 *	NMH's Simple C Compiler, 2012
 *	perror()
 */
#define _ELFCLIB_
#include <stdio.h>
#include <string.h>
#include <errno.h>

/* define only extern procedures required */
#pragma           extrn Cfprintf
#pragma           extrn Cstderr
#pragma           extrn Cerrno
#pragma           extrn Cstrerror
#pragma .link .library string.lib

void perror(const char *msg) {
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
}
