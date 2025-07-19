
#ifndef _STDLIB_
#define _STDLIB_

/* don't define all external functions inside C libraries to prevent dupes */
#ifndef _ELFCLIB_ 
#pragma             extrn C_init
#pragma             extrn C_fdinit
#pragma             extrn C_fdcnt
#pragma             extrn Cabort
#pragma             extrn Cabs
#pragma             extrn Catexit    
#pragma             extrn Catoi    
#pragma             extrn Cbsearch           
#pragma             extrn Ccalloc    
#pragma             extrn Cdiv 
#pragma             extrn Cexit            
#pragma             extrn Cfree  
#pragma             extrn Citoa           
#pragma             extrn Citox
#pragma             extrn Citou           
#pragma             extrn Cmalloc
#pragma             extrn Cqsort
#pragma             extrn Crand
#pragma             extrn Csrand
#pragma             extrn Ccreat
#pragma             extrn Copen
#pragma             extrn Cclose
#pragma             extrn Cread
#pragma             extrn Cwrite
#pragma             extrn Clseek
#endif

#ifndef SEEK_SET
#define SEEK_SET	0
#endif 

#ifndef SEEK_CUR
#define SEEK_CUR	1
#endif

#ifndef SEEK_END
#define SEEK_END	2
#endif 

#ifndef FD_SIZE
#define FD_SIZE   532
#endif

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

/* fcntl constants mapped to Elf/OS constants */
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

#ifndef EXIT_ERROR
#define  EXIT_ERROR  (-1)
#endif 

typedef struct {
    int quot;       /* quotient */
    int rem;        /* remainder */
} div_t;


void _init(void);
int _fdinit(void);
void abort(void);
int abs(int n);
int atexit(int (*fn)());
int atoi(char *s);
void *bsearch(void *key, void *array, int count, int size, int (*cmp)());
void *calloc(int count, int size);
void div(int num, int denom, div_t *rp);
void exit(int n);
void free(void* p);
void itoa(int n, char *s);
void itox(int n, char *s);
void itou(int n, char *s);
void* malloc(int size);
void qsort(void *list, int count, int size, int (*cmp)());
int rand(void);
void srand(int n);
/* unistd file functions */
int	 creat(char *path, int mode);
int	 open(char *path, int flags);
int	 close(int fd);
int	 read(int fd, void *buf, int len);
int	 write(int fd, void *buf, int len);
int  unlink(char *pat);
int	 rename(char *old, char *new);
int  lseek(int fd, int hi_off, int lo_off, int how);
#endif
