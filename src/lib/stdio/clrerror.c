#define _ELFCLIB_
#include <stdio.h>

void clrerror(FILE *f) {
	//grw - clear error and eof flag bits
	if (f != NULL) {
    f->iom &= ~_FERROR;
	  f->iom &= ~_FEOF;	
	}
}
