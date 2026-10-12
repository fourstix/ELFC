#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn C_conin
#pragma             extrn C_conecho

/* maximum number of characters read, not counting the null */
#define _GETSTR_MAX   255

/*
 * ELF-DOS has no kernel function to read a line of input, so the line
 * is read here a character at a time.  Input ends with a carriage
 * return or newline, which is not stored, or with Ctrl-C or the end
 * of redirected input.
 */
char* _getstr(char *s) {
  char* p;
  int ch;
  int n;

  p = s;
  if (p != NULL) {
    n = 0;
    for (;;) {
      ch = _conin();

      if (ch == '\r' || ch == '\n') {
        _conecho(ch);
        break;
      }

      if (ch == 0 || ch == 3)
        break;

      /* backspace or delete removes the last character */
      if (ch == 8 || ch == 127) {
        if (n > 0) {
          n--;
          p--;
          _conecho(8);
          _conecho(' ');
          _conecho(8);
        }
        continue;
      }

      if (n < _GETSTR_MAX) {
        *p++ = ch;
        n++;
        _conecho(ch);
      }
    }
    *p = 0;
  }
  return s;
}
