#ifndef _STDIO_
#define _STDIO_

/* include stdlib if not included already */
#ifndef _STDLIB_
#include <stdlib.h>
#endif

/* Maximum size of string in Elf/OS is 255 bytes */
#ifndef _BUFLEN
#define _BUFLEN 256
#endif

#ifndef EOF
#define EOF (-1)
#endif

#ifndef NULL
#define NULL (void*)0
#endif

#ifndef FOPEN_MAX
#define FOPEN_MAX 7
#endif

#ifndef FILENAME_MAX
#define FILENAME_MAX 128
#endif

#ifndef TMP_MAX
#define TMP_MAX 64
#endif

#ifndef TMP_FMT
#define TMP_FMT "temp.%02d"
#endif

#ifndef L_tmpnam
#define L_tmpnam 8
#endif

#ifndef _IONBF
#define _IONBF 0
#endif

#ifndef _IOSYS
#define _IOSYS 1
#endif

#ifndef _IOTMP
#define _IOTMP 2
#endif

#ifndef _FCLOSED
#define _FCLOSED 0
#endif

#ifndef _FREAD
#define _FREAD 1
#endif

#ifndef _FWRITE
#define _FWRITE 2
#endif

#ifndef _FERROR
#define _FERROR 4
#endif

#ifndef _FEOF
#define _FEOF 8
#endif

typedef struct {
  int fd;
  int iom;
  int last;
  int mode;
  int ch;
  int tmpid;
} FILE;

extern FILE *stdin, *stdout, *stderr;

#ifndef getc
#define getc fgetc
#endif

#ifndef putc
#define putc fputc
#endif

#ifndef getchar
#define getchar() fgetc(stdin)
#endif

#ifndef putchar
#define putchar(x) fputc(x, stdout)
#endif

#ifndef SEEK_SET
#define SEEK_SET 0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR 1
#endif

#ifndef SEEK_END
#define SEEK_END 2
#endif

typedef struct {
  int hi; /* position hi address word */
  int lo; /* position lo address word */
} pos_t;

/* unbuffered system IO functions */
char* gets(char* buf);
int puts(const char* s);
int putstr(const char* s);
int getch(void);
int putch(int ch);

/* buffered IO functions */
int fgetc(FILE* f);
int fputc(int c, FILE* f);
char* fgets(char* s, int len, FILE* f);
int fputs(const char* s, FILE* f);
int ungetc(int c, FILE* f);

/* buffered file functions */
FILE* fdopen(int fd, int iomode);
int fclose(FILE* f);
FILE* fopen(const char* path, const char* mode);
size_t fread(void* p, size_t size, size_t count, FILE* f);
size_t fwrite(const void* p, size_t size, size_t count, FILE* f);
int fflush(FILE* f);

/* print functions */
int fprintf(FILE* f, const char* fmt, ...);
int printf(const char* fmt, ...);
int sprintf(char* buf, const char* fmt, ...);
int kprintf(int fd, const char* fmt, ...);
int vfprintf(FILE* f, const char* fmt, void** args);
int vprintf(const char* fmt, void** args);
int vsprintf(char* buf, const char* fmt, void** args);

/* scan functions */
int fscanf(FILE* f, const char* fmt, ...);
int scanf(const char* fmt, ...);
int sscanf(char* src, const char* fmt, ...);

/* file functions */
int remove(const char* path);
int rename(const char* old, const char* new);
int fileno(FILE* f);
char* tmpnam(char* buf);
FILE* tmpfile(void);

/* file position functions */
int fgetpos(FILE* f, pos_t* pos);
int fsetpos(FILE* f, pos_t* pos);
int fseek(FILE* f, int offset, int how);
int ftell(FILE* f);
void rewind(FILE* f);

/* error functions */
int ferror(FILE* f);
int feof(FILE* f);
void clearerr(FILE* f);
void perror(const char* msg);
#endif
