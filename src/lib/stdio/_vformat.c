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

#pragma             extrn C_lbuf
#pragma             extrn Cputs
#pragma             extrn Cputch
#pragma             extrn Citoa
#pragma             extrn Cabs
#pragma             extrn Cmemcpy
#pragma             extrn Citox
#pragma             extrn C_fwrite
#pragma             extrn Cwrite
#pragma             extrn Cputstr
#pragma             extrn Cstrchr
#pragma             extrn Cstrlen
#pragma             extrn Cmalloc
#pragma             extrn Cfree
#pragma             extrn Cerrno
#pragma             extrn Cisdigit
#pragma .link .requires Cfwrite
#pragma .link .library string.lib
#pragma .link .library ctype.lib
#pragma .link .requires Cctype

int _fwrite(void *buf, int len, FILE *f);

extern char *_lbuf;

static int	ofd;
static FILE	*outf;
static int	olen;
static int	limit;
static char	*vbuf;
static int	err;

/*
 * Convert integer N to string. Write the string to P.
 * P must point to the *end* of the buffer initially;
 * the output is written backwards!
 *
 * BASE is the numeric base (8,10,16). SGNCH points
 * to a buffer to which ritoa writes the sign of N. The
 * sign is *not* included in the buffer P.
 *
 * When BASE is negative, upper case letters will be
 * used in hexa-decimal formatting.
 *
 * Octal and hexadecimal numbers are converted as 
 * unsigned values.
 */
static char *bitoa(char *p, int n, int base, char *sgnch) {
	int	s = 0, a = 'a';
	int d;
	/* set null at end of string */
	*--p = 0;
	if (base < 0) base = -base, a = 'A';
	if (0 == n) {
		/* zero is the same for every base */
		*--p = '0';
	} else if (10 == base) {
		/* signed integer */
		if (n < 0) s = 1, n = -n;

		while (n) {
			*--p = (n % base) + '0';
			n = (n/base);
		} //while
	} else if (16 == base) {
			/* hex */
			do {
				*--p = (n & 0x000F) + '0';
				if ((n & 0x000F) > 9) *p += a-10-'0';
				n >>= 4;
			} while (n);
	} else {
		  /* octal */
		  do {
			  *--p = (n & 0x0007) + '0';
			  n >>= 3;
			} while(n);
	}	
	if (s) *sgnch = '-';
	return p;
}

static void append(char *what, int len) {
	int	k;
	
	if (0 == len) {
		return;
	}
	//grw - write everything as a string buffer
	k = limit-olen-1;
	len = len < k ? len : k;
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
 * In MODE==0, write at most MAX characters to DEST
 * where MAX==0 means unlimited).
 */

int _vformat(int mode, int max, void *dest, char *fmt, void **varg) {

	char	*p, *end;
//	char	*lbuf, *p, *end;
	int	left, len, alt, k;
	char	pad[1], sgnch[2], *pfx;
	int	na = 0;
	//grw - implement a smaller buffer
	static char sbuf[8];

  if (mode != 0) {
	  //lbuf = (char *) malloc(_BUFLEN);
		
		/* check for out of memory */
		if (_lbuf == NULL) {
			errno = ENOMEM;
			return -1;
		}
  }	
	//grw - implement a smaller buffer
	//end = &lbuf[_BUFLEN];
	end = &sbuf[8];
	sgnch[1] = 0;

	if (0 == mode) {
		outf = NULL;
		ofd = -1;
		vbuf = dest;
		*vbuf = 0;
	}
	else if (-1 == mode) {
		outf = NULL;
		ofd = (int) dest;
		err = 0;
		vbuf = _lbuf;
		*vbuf = 0;
	}
	else {
		outf = dest;
		ofd = -1;
		err = 0;
		vbuf = _lbuf;
		*vbuf = 0;
	}

	olen = 0;
	if (0 == max)
		limit = _BUFLEN;
	else	
 	  limit = max;

	while (*fmt) {
		left = len = 0;
		*sgnch = 0;
		pfx = "";

		if ('%' == *fmt) {
			//puts("format");
			fmt++;
			*pad = ' ';
			alt = 0;

			while (*fmt && strchr("-+0 #", *fmt)) {
				if ('-' == *fmt) {
					left = 1, *pad = ' ';
					fmt++;
				}
				else if ('0' == *fmt) {
					if (!left) *pad = '0';
					fmt++;
				}
				else if ('#' == *fmt) {
					alt = 1;
					fmt++;
				}
				else if ('+' == *fmt) {
					*sgnch = '+';
					fmt++;
				}
				else if (' ' == *fmt) {
					if (!*sgnch) *sgnch = ' ';
					fmt++;
				}
			}

			if ('*' == *fmt)
				len = (int) *varg++, fmt++;
			else
				while (isdigit(*fmt)) {
					len = len * 10 + *fmt++ - '0';
				}
		
			switch (*fmt++) {
			case 'c':
				*pad = ' ';
				*sgnch = 0;
				//grw - implement a smaller buffer
				sbuf[0] = (char) *varg++;
				sbuf[1] = 0;
				p = sbuf;
				na++;
				break;
			case 'd':
			case 'i':
				p = bitoa(end, (int) *varg++, 10, sgnch);
				na++;
				break;
			case 'n':
				p = bitoa(end, olen, 10, sgnch);
				break;
			case 'o':
				p = bitoa(end, (int) *varg++, 8, sgnch);
				if (alt) pfx = "0";
				//grw - octal is always unsigned
				*sgnch = 0;
				na++;
				break;
			case 's':
				*sgnch = 0;
				*pad = ' ';
				p = *varg++;
				if (NULL == p) p = "(NULL)";
				na++;
				break;
			case 'p':
				//grw - reworked pointer to use Elf/OS function
				//p = ptoa(end, (int) *varg++);
				p = sbuf;
				itox((int) *varg++, p);
				pfx = "0x";
				//grw - length is always six with no padding required
				//len = BPW*2+2;
				//*pad = '0';
				len = 6;
				//grw - Elf/OS pointer is always unsigned
				*sgnch = 0;
				na++;
				break;
			case 'x':
			case 'X':
				k = 'X' == fmt[-1]? -16: 16;
				p = bitoa(end, (int) *varg++, k, sgnch);
				if (alt) pfx = k<0? "0X": "0x";
				//grw - hex is always unsigned
				*sgnch = 0;
				na++;
				break;
			default:
			  //grw - implement a smaller buffer
				sbuf[0] = fmt[-1];
				sbuf[1] = 0;
				p = sbuf;
				break;
			}
		}
		else {
			//grw - implement a smaller buffer
			sbuf[0] = *fmt++;
			sbuf[1] = 0;
			p = sbuf;
		}

		k = strlen(p) + strlen(pfx) + strlen(sgnch);
		
		if ('0' == *pad) {
			if (*sgnch) append(sgnch, 1);
			append(pfx, strlen(pfx));
			pfx = "";
		}
		
		while (!left && len-- > k) {
			append(pad, 1);
		}
		if (*sgnch && *pad != '0') {
			append(sgnch, 1);
			append(pfx, strlen(pfx));
		}
		if (!*sgnch) {
			append(pfx, strlen(pfx));
		}

		append(p, strlen(p));

		while (left && len-- > k) {
			append(pad, 1);
		}
		if (outf && err) break;
	}
	if (mode != 0) {
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
					outf->iom &= _FERROR;
					na = -1;	
				}
		}		
		/* free the line buffer memory */
		//free(lbuf);
  }
	return na;
}
