#ifndef _STDIO_
#define _STDIO_

#pragma .link .library stdio.lib
#pragma             extrn Cputs
#pragma             extrn Cgets

#ifndef EOF
#define  EOF  (-1)
#endif 

#ifndef NULL
#define  NULL (void*)0
#endif 

/*
#define FOPEN_MAX	20
#define BUFSIZ		512
#define FILENAME_MAX	128
#define TMP_MAX		1
#define L_tmpnam	8

#define _IONBF	0
#define _IOLBF	1
#define _IOFBF	2
#define _IOACC	3
#define _IOUSR	4

#define _FCLOSED	0
#define _FREAD		1
#define _FWRITE		2
#define _FERROR		4

typedef struct {
	int	fd;
	char	iom;
	char	last;
	char	mode;
	int	ptr;
	int	end;
	int	size;
	int	ch;
	char	*buf;
} FILE;

extern FILE	*stdin, *stdout, *stderr;

#define getc	fgetc
#define putc	fputc

#define SEEK_SET	0
#define SEEK_CUR	1
#define SEEK_END	2
*/

char	*gets(char *buf);
int	 puts(char *s);

#endif
