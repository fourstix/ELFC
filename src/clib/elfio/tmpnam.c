#define _ELFCLIB_
#include <stdio.h>
#include <string.h>

#pragma             extrn Csprintf
#pragma             extrn Cfopen
#pragma             extrn Cfclose
#pragma             extrn Cstrcpy

#pragma .link .library string.lib

/* need to declare variable public for linker */
#pragma 						public C_tmpid

static int	_tmpid = 0;
	
char *tmpnam(char *buf) {

	static char	tmp[L_tmpnam];
	FILE		*f;

	for (;;) {
		sprintf(tmp, TMP_FMT, _tmpid);
		if (++_tmpid > TMP_MAX) return NULL;
		 /* check to see if filename already exists */
		if ((f = fopen(tmp, "r")) == NULL) {
			/* if no file exists, return name */
			if (buf) {
				strcpy(buf, tmp);
				return buf;
			}
			return tmp;
		}
		/* close existing file and try again */
		fclose(f);
	}
}
