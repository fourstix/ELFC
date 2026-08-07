#define _ELFCLIB_
#include <stdio.h>
#include <string.h>


#pragma             extrn Cputs
#pragma             extrn C_fwrite
#pragma             extrn Cstrlen
#pragma .link .requires Cfwrite
#pragma .link .library string.lib

int fputs(const char *s, FILE *f) {
	int	k;

  k = strlen(s);

	/* fputs doesn't append newline at end of string */
	if (f->mode == _IOSYS) {
		_putstr(s);
  } else if (_fwrite(s, k, f) != k)
    return EOF;
  return k;

}
