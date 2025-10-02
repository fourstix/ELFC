
#ifndef _STDLIB_
#define _STDLIB_

#ifdef _STGROM_
#pragma #define STGROM
#define BRKPT asm("     brkpt    ;---- jump to routine in stg rom\n");
#else 
#define BRKPT  
#endif

/* don't define all external functions inside C libraries to prevent dupes */
#ifndef _ELFCLIB_ 
#pragma #include include/stdlib.inc
#endif

/* file descriptor constants */
#ifndef FD_MAX
#define FD_MAX  7
#endif

/* start of system file descriptors */
#ifndef FD_SYS
#define FD_SYS  3
#endif

#ifndef FD_SIZE
#define FD_SIZE   534
#endif

/* file descriptor constants */
#ifndef FD_MAX
#define FD_MAX  7
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

typedef struct {
    int quot;       /* quotient */
    int rem;        /* remainder */
} div_t;

void _init(void);
int _fdinit(void);
int _fildes(int fd);
void abort(void);
void exit(int n);
int atexit(int (*fn)());
void* malloc(size_t size);
void *calloc(size_t count, size_t size);
void *realloc(void* p, size_t size);
void free(void* p);
int atoi(char *s);
void itoa(int n, char *s);
void itox(int n, char *s);
void itou(unsigned int n, char *s);
int abs(int n);
void div(int num, int denom, div_t *rp);
void *bsearch(void *key, void *array, size_t count, size_t size, int (*cmp)());
void qsort(void *list, size_t count, size_t size, int (*cmp)());
int rand(void);
void srand(int n);
int min(int a, int b);
int max(int a, int b);

/* unistd file functions */
int	 creat(char *path, int mode);
int	 open(char *path, int flags);
int	 close(int fd);
int	 read(int fd, void *buf, size_t len);
int	 write(int fd, void *buf, size_t len);
int  unlink(char *path);
int  lseek(int fd, int hi_off, int lo_off, int how);
#endif
