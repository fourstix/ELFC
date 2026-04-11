/*
 *	NMH's Simple C Compiler, 2011--2014
 *	_vformat()
 */
#define _ELFCLIB_
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

//#define BPW 2

#pragma             extrn Citoa
#pragma             extrn Citou
#pragma             extrn Cmemcpy
#pragma             extrn Citox
#pragma             extrn C_fwrite
#pragma             extrn Cwrite
#pragma             extrn Cputstr
#pragma             extrn Cstrlen
#pragma             extrn Cerrno
#pragma .link .requires Cfwrite
#pragma .link .library string.lib

int _fwrite(void *buf, int len, FILE *f);

static int	ofd;
static FILE	*outf;
static int	olen;
//static int	limit;
static char	*vbuf;
static int	err;

static void append(char *what) {
	int len = strlen(what);
	if (0 == len) {
		return;
	}
	//grw - write everything as a string buffer
	//k = limit-olen-1;
	//len = len < k ? len : k;
	memcpy(vbuf + olen, what, len);
	olen += len;
	vbuf[olen] = 0;
}

/*
 * Format and write output in the style of PRINTF.
 * When MODE==0, write the output to DEST (assuming
 * that DEST is a CHAR*).
 * When MODE==1, assume that DEST is a FILE* and
 * write the output to that stream.
 * When MODE==-1, assume that DEST is a unix file
 * descriptor and write the output to that fd.
 * In MODE==0, write at most MAXC characters to DEST
 * where MAXC==0 means unlimited).
 */

 //grw - changed max to maxc to avoid conflict with macro names

int _vformat(int mode, void *dest, char *fmt, void **varg) {
	char	*p;
	int	len, k;
	int	na = 0;
	//grw - implement a smaller buffer
	static char sbuf[8];

	if (0 == mode) {
		outf = NULL;
		ofd = -1;
		vbuf = dest;
		*vbuf = 0;
	} else if (-1 == mode) {
		outf = NULL;
		ofd = (int) dest;
		err = 0;
		vbuf = sbuf;
		*vbuf = 0;
	} else {
		outf = dest;
		ofd = -1;
		err = 0;
		vbuf = sbuf;
		*vbuf = 0;
	}

	olen = 0;

	while (*fmt) {
		len = 0;

		if ('%' == *fmt) {
			fmt++;

			switch (*fmt++) {
			case 'c':
				//grw - implement a smaller buffer
				sbuf[0] = (char) *varg++;
				sbuf[1] = 0;
				p = sbuf;
				na++;
				break;
			case 'd':
			  p = sbuf;
				itoa((int) *varg++, p);
				na++;
				break;
			case 's':
				p = *varg++;
				if (NULL == p) p = "(NULL)";
				na++;
				break;
			case 'u':
				p = sbuf;
				itou((unsigned)*varg++, p);
				na++;
				break;
			case 'p':
			case 'x':
			  p = sbuf;
				itox((int) *varg++, p);
				na++;
				break;

			default:
			  //grw - implement a smaller buffer
				sbuf[0] = fmt[-1];
				sbuf[1] = 0;
				p = sbuf;
				break;
			}
		}	else {
			sbuf[0] = *fmt++;
			sbuf[1] = 0;
			p = sbuf;
		}

	  if (outf && err) break;

	  if (mode != 0) {
		  olen = strlen(p);
		  /* write out buffer to file */
		  if (ofd != -1) {
			  if (write(ofd, vbuf, olen) != olen) {
				  errno = EIO;
				  na = -1;
			  }
		  }	else {
		    outf->last = _FWRITE;
			  /* short-circuit to speed up printf output */
			  if (_IOSYS == outf->mode) {
				/* print direct to stdout */
				putstr(vbuf);
		  	} else if (_fwrite(vbuf, olen, outf) != olen) {
					errno = EIO;
					outf->iom |= _FERROR;
					na = -1;
			  }
		  }
    } else {
		  append(p);
    }
  }
	return na;
}
