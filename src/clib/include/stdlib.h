
#ifndef _STDLIB_
#define _STDLIB_

#ifdef _STGROM_
#define BRKPT_ADDR  $F000
#pragma #define BRKPT_ADDR  $F000
#endif

#ifdef _MAXMON_
#define BRKPT_ADDR  $F034
#pragma #define BRKPT_ADDR $F034
#endif

#ifdef BRKPT_ADDR
#define BRKPT asm("     brkpt    ;---- jump to routine in stg rom\n");
#else
#define BRKPT
#endif


#ifndef int32
struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};
#endif

/* file descriptor constants */

/* Max number of 8 = 3 pre-defined + 5 system files */
#ifndef FD_MAX
#define FD_MAX  8
#endif

/* start of system file descriptors */
#ifndef FD_SYS
#define FD_SYS  3
#endif

#ifndef FD_SIZE
#define FD_SIZE   534
#endif

extern int _fdtable[FD_MAX];

/* file position constnts */
#ifndef SEEK_SET
#define SEEK_SET	0
#endif

#ifndef SEEK_CUR
#define SEEK_CUR	1
#endif

#ifndef SEEK_END
#define SEEK_END	2
#endif

/* fcntl constants mapped to Elf/OS constants */
#ifndef O_OPEN
#define O_OPEN    0
#endif

#ifndef O_CREAT
#define O_CREAT   1
#endif

#ifndef O_TRUNC
#define O_TRUNC   2
#endif

#ifndef O_APPEND
#define O_APPEND  4
#endif

#ifndef O_EXECUTE
#define O_EXECUTE 8
#endif

#ifndef O_RDONLY
#define O_RDONLY 16
#endif

/* Read/Write is the default open mode in Elf/OS */
#ifndef O_RDWR
#define O_RDWR    0
#endif

/* Elf/OS has no write-only mode so map to default */
#ifndef O_WRONLY
#define O_WRONLY    0
#endif

#ifndef EOF
#define  EOF  (-1)
#endif

#ifndef NULL
#define  NULL (void*)0
#endif

#ifndef EXIT_SUCCESS
#define  EXIT_SUCCESS  (0)
#endif

#ifndef EXIT_FAILURE
#define  EXIT_FAILURE  (1)
#endif

#ifndef EXIT_ERROR
#define  EXIT_ERROR  (-1)
#endif

#ifndef RAND_MAX
#define RAND_MAX	65535
#endif

/* typedef's from stddef.h */
typedef unsigned int size_t;
typedef unsigned int ptrdiff_t;
typedef unsigned int wchar_t;
typedef unsigned int max_align_t;

/* typedef for div function */
typedef struct {
    int quot;       /* quotient */
    int rem;        /* remainder */
} div_t;

/* Absolute value */
#ifndef abs
#define abs(n) (((n) < 0) ? -(n) : (n))
#endif

/* Minimum value */
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif

/* Maximum value */
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

void _init(void);
int _fdinit(void);
int _fildes(int fd);
void abort(void);
void exit(int n);
int atexit(int (*fn)());
void *malloc(size_t size);
void *calloc(size_t count, size_t size);
void *realloc(void* p, size_t size);
void free(void* p);
int atoi(const char *s);
void itoa(int n, char *s);
void itox(int n, char *s);
void itou(unsigned int n, char *s);
div_t div(int num, int denom);
void *bsearch(void *key, void *array, size_t count, size_t size, int (*cmp)());
void qsort(void *list, size_t count, size_t size, int (*cmp)());
int rand(void);
void srand(int n);

typedef struct int32 off_t;

/* unistd file functions */
int creat(char *path, int mode);
int open(char *path, int flags);
int close(int fd);
int read(int fd, void *buf, size_t len);
int write(int fd, void *buf, size_t len);
int unlink(char *path);
int lseek(int fd, int offset, int whence);
off_t lseek32(int fd, off_t *offset, int whence);
#endif
