#ifndef _EDOS_
#define _EDOS_

/*
 * ELF-DOS kernel interface for the edosstd library.
 *
 * The asm() statements in this library call the kernel by name, using
 * the kernel API include file from the ELF-DOS SDK.  The compiler puts
 * that file into the generated assembly file when the -E option is used.
 * Without it, the #pragma line does so, with a path that is relative to
 * this folder, which is where the library is built.
 */

#ifndef __ELFDOS__
#pragma #include ../elfdos-sdk/include/kernel_api.inc
#endif

/*
 * The kernel may change any register that a call does not return a value
 * in, so the registers ElfC reserves are saved around every kernel call.
 * R7 is the expression stack pointer, R9 the subroutine pointer and RB
 * the stack frame base pointer.  POP changes D but leaves DF alone.
 */
#define _KSAVE     asm("         push r7         ; save ESP"); asm("         push r9         ; save subroutine pointer"); asm("         push rb         ; save stack frame base pointer");
#define _KRESTORE  asm("         pop  rb         ; restore stack frame base pointer"); asm("         pop  r9         ; restore subroutine pointer"); asm("         pop  r7         ; restore ESP");

/* Set RA to 0 when DF = 0 (success) or to -1 when DF = 1 (failure) */
#define _KRESULT   asm("         ldi  0          ; set default value for success"); asm("         lsnf            ; DF = 0, means success"); asm("         ldi  $Ff        ; otherwise set result for error"); asm("         phi  ra         ; set result for 0 or -1 "); asm("         plo  ra         ; set result in ra ");

/*
 * K_FILE_OPEN modes
 *   _K_READ    read only, the file must exist
 *   _K_WRITE   read and write, the file is truncated or created
 *   _K_APPEND  read and write, positioned at the end, the file is created
 */
#define _K_READ     0
#define _K_WRITE    1
#define _K_APPEND   2

/*
 * Each open file needs a 32 byte File Control Block followed by its own
 * 512 byte sector buffer.  The kernel refuses an FCB that crosses a page
 * boundary, so the FCB is placed on a 32 byte boundary inside a larger
 * block from malloc.  The word below the FCB holds the address malloc
 * returned, so the block can be freed again.
 *
 *    malloc block  : 2 to 33 bytes of padding, ending in the block address
 *    FCB           : 32 bytes, 32 byte aligned  <-- value in _fdtable
 *    sector buffer : 512 bytes
 */
#define _FCB_LEN     32
#define _FCB_IOBUF   512
#define _FCB_ALLOC   (_FCB_LEN + _FCB_IOBUF + 33)
#define _FCB_BLOCK(fildes)   (*((int *)(fildes) - 1))

/* memory heap, kept by heap_malloc in the ELF-DOS SDK */
extern int _hinit;
void _heapinit(void);

/* ELF-DOS support functions */
int _conin(void);
int _conecho(int ch);

#endif
