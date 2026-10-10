#define _ELFCLIB_
#include <stdio.h>

/* Elf/OS is write through so fflush does nothing */

int fflush(FILE * f) {
return 0;
}
