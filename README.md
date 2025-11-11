# ELFC
A C compiler for a CDP1802 based microcomputer running Elf/OS or Mini/DOS.  ElfC is based on SubC written by Nils M Holms.

Installation
-------------
* Unzip the file elfc_r21.zip into the desired directory
* Copy the file `hello.c` into the directory.
* Use the command *elfc hello.c* to compile the `hello.c` to `hello.elfos`
* Transfer the `hello.elfos` file to a microcomputer running Elf/OS or Mini/DOS.
* Make the file executable using the *chmod +x hello.elfos* command
* Run the command *hello.elfos* to view the "Hello, World!" message

Design Goals
-------------
* Use the [Asm/02](https://github.com/fourstix/Asm-02) assembler and the [Link/02](https://github.com/fourstix/Link-02) linker to produce CDP1802 binary code to run as an Elf/OS or Mini/DOS program
* Create a library based on Mike Riley's [Library/02](https://github.com/rileym65/Library-02) standard library.
* Target both Elf/OS and Mini/DOS as a platform.
* Target Windows and Linux as the development platform (cross-compiler)
* Use an expression stack similar to the one implemented in Mike Riley's Fortran/02 program.
* Minimize changes to basic SubC compiler code and prefer changes to the code generation and library code functions.
* Implement the code generation functions first, migrate to the latest version of SubC and then work on implementing the C libraries.
* Extend the SubC code to cover additional C keywords and functions.

Release 1
----------

This version is based on the [SubC book version, 2nd Ed.](https://www.t3x.org/subc/README-2nd-ed.html) described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms.

I strongly recommend reading Nils's book.  Practical Compiler Construction is a very good guide in explaining the theory behind the SubC compiler as well as describing the compiler's code.  The second edition can be ordered as a [paperback](https://www.lulu.com/en/us/shop/nils-m-holm/practical-compiler-construction/paperback/product-179kp29q.html) or [pdf ebook file](https://www.lulu.com/en/us/shop/nils-m-holm/practical-compiler-construction/ebook/product-18knr78q.html) from Lulu press.

In Release 1 the code generation functions for Elf/OS and Mini/DOS have all been implemented.  The arithmetic and logical operators have all been implemented and tested.


Release 2
----------
This release migrates the code base to the current [Experimental SubC](https://www.t3x.org/subc/index.html) version so that the code generator can include structures, unions and typedefs.

This release supports some basic code optimization as described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms

The compiler supports the [Asm/02](https://github.com/fourstix/Asm-02) and [Link/02](https://github.com/fourstix/Link-02) linker better, and included files and libraries are better organized.

The C runtime module `crt0` now holds the start-up code for the program.  The start up code now pushes the expected command line arguments for `main` onto the stack (`int argc` and `char **argv`) and then calls the main function.

An additional compiler option `-L` will compile and assemble Elf/OS (Min/iDOS) library modules from C files.

The stdlib, stdio, ctype, and string C libraries are supported as described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms.

* The C libraries are created from C files using the ElfC (`-L`) library compile option.

* The header files use `#pragma` statements so the libraries link properly.

More information about unsupported library functions, header files and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.

Release 2.5
------------

This release adds an implementation of the C time library to ElfC, and a compiler option -N to compile without linking the C stdlib and stdio libraries.

More information about the time library functions, header files and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.

Release 2.1
------------

This release passes all the functional tests from the [Experimental version of SubC](https://www.t3x.org/subc/index.html).  No new function was added to this release, only a few minor issues were fixed in this release.  The functional test cases are included in this release.

Version 2
----------

* Version 2 implements the code generation functions required to compile a C file and assemble the resulting CDP1802 assembly and link code files into a binary program for the Elf/OS (Mini/DOS) operating system.

* The assembler [Asm/02]((https://github.com/fourstix/Asm-02)) and linker [Link/02](https://github.com/fourstix/Link-02) are now invoked with the same path as the compiler.  The C library files and header files are located in the same manner, so that the preprocessor commands `#include <header.h>` and `#include "header.h"` work as expected.

* Version 2 extends the library of arithmetic and variable functions based on the  16-bit standard library [Library/02](https://github.com/rileym65/Library-02) to manipulate values on an expression stack.

* This version implements the changes to the book compiler code contained in the latest current [Experimental version of SubC](https://www.t3x.org/subc/index.html).

* The peep-hole code optimizations are all implemented except for the 386 assembly code Type Synthesis optimizations which have no equivalents available in 1802 assembly code.  In the discussion *RISC vs CISC* on page 362 of [Practical Compiler Construction](https://www.t3x.org/reload/index.html), Nils M Holm covers this topic in more detail.

* In addition to these optimizations, jump optimizations and push / pop optimizations were added that are specific to 1802 assembly code.  Constant folding and AST trees are supported as in the [Experimental SubC](https://www.t3x.org/subc/index.html) code.

* The `asm` statement passes a string literal directly into the generated assembly file.

* The `#pragma` preprocessor directive can be used to directly insert an assembly directive or a line of assembly code directly into the generated assembly file.

* The `__LINE__` and `__FILE__` preprocessor directives were implemented in this version.

* The arguments `int argc` and `char **argv` are now available as arguments to main.  Up to eight arguments are supported.  The argument `argv[0]` points to the command string that invoked the program.

* The `stdlib`, `stdio`, `ctype`, and `string` are supported.

* The ElfC compiler now accepts inline comments (`// comments`) as well as traditional C commments (`/* comments */`).

* The ElfC compiler now accepts `\e` as an escape sequence for the ASCII escape character 0x1B.

* `struct`, `union` and `typedef` are now supported, except as function arguments and function return values.

* Pointers to `struct`, `union` and `typedef` are now supported. A function may accept a *pointer* to a `struct` or `union` and a function may return a *pointer* to a `structure` or `union`.

* `&array` is now valid syntax (you no longer have to write `&array[0]`).

* The `auto`, `register`, and `volatile` keywords are recognized (as no-ops).

* `enum`'s may now be local.

* `extern` identifiers may now be declared locally.

* Prototypes may have the `static` storage class.

* The `#error`, `#line`, and `#pragma` commands have been added.

* The `atexit()` mechanism is now supported.

* The `varags` mechanism is now supported as functions as described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms.

* The `assert` macro is implemented as a function with support for the `NDEBUG` macro.

* STG ROM break points are supported by the `_STGROM_` and `BRKPT` macros.

* A broader subset of C expression syntax is accepted in constant expression contexts. Pointer variables can be initialized with NULL.

More information about unsupported library functions, header files and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.


Compiler Option Changes
-----------------------
* Added the `-L` (Library) ElfC option to compile and assemble a C source file into a prg file defining an Elf/OS (Mini/DOS) library procedure.

* The `-N` (No libraries) option compiles without the stdio and stdlib C libraries.  The user should supply the _init() function that is called by ElfC before the main function.

* Simplified the `-V` (Verbose) option to display *all* verbose messages or none. There is no longer any need to specify multiple verbose options for additional messages.

More information about `-L` Library option can be found on the [ELFC Detailed Information](ELFC.md) page.

Version 3
----------

* Version 3 adds support for the `signed` and `unsigned` keywords.

* This version implements a subroutine scheme for frequently used routines in the ElfC library to improve performance.

* The generated code creates a string table for improved performance.

* The stdlib defines the `size_t` type and the C library functions were updated to use this type.

* The unsigned conversion `%u` is supported by the stdio printing and scanning functions.

* Several functions were replaced by inline assembly code to remove dependencies on BIOS functions.

* The included files were cleaned up to eliminate unused definitions, and the kerneal api were moved to  a separate included file.

More information about Version 3, signed and unsigned types, library functions and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.

Release 3.1
------------
*  This release removes the restriction of only 2 levels of pointer indirection and supports up to 15 levels of indirection. This meets the ANSI specified minimum of 12 levels of indirection.

* This release adds support for local labels and the `goto` keyword.

* The `const` keyword is now supported.

* Functions may now return a structure or union.

* Structures and unions may now be assigned.

* ElfC can now emit warning messages when compiling code.

* Pointers may now be initialized with non-zero constant address values, like *0xFF00*

* The `__FUNC__` preprocessor directive was added in this version.

* Declaring a variable as `volatile` will now prevent optimizations on that variable.

* Global and static arrays may be initialized using initializer list or string. ElfC will
  emit an error message if the initializer list size does not match the size of the array.

More information about Version 3.1, labels, `goto`, `volatile` and `const` keywords, library functions and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.

Stdlib Library
--------------
**The following functions are supported in the ElfC stdlib C library.**

**Program Exit Functions**
* void abort(void);
* int atexit(int (*fn)());
* void exit(int n);

*Notes:*
* *`abort` terminates a program immediately without closing any open files.*
* *`exit` will call the function registered by `atexit`, then close any open files by calling `fclose`, and then terminate the program.*
* *`exit` deletes any temporary files created by `tmpfile` by closing them with `fclose`.*
* *Only one function can be registered by `atexit`.*


**Memory Allocation**

* void \*malloc(size_t size);
* void \*calloc(size_t count, size_t size);
* void \*realloc(void \*p, size_t size);
* void free(void\* p);

**Number Conversion**
* int atoi(const char \*s);
* void itoa(int n, char \*s);
* void itox(int n, char \*s);
* void itou(unsigned int n, char \*s);

*Note: `itox` and `itou` are functions for hexadecimal and unsigned integer conversion.*

**Math Utilities**

* int abs(int n);
* div_t div(int num, int denom);
* void \*bsearch(void \*key, void \*array, size_t count, size_t size, int (\*cmp)());
* void qsort(void \*list, size_t count, size_t size, int (\*cmp)());
* int rand(void);
* void srand(int n);
* int min(int a, int b);
* int max(int a, int b);

**The following unistd.h file functions are included in the ElfC stdlib C library.**

**Low Level File Functions**

* int	 creat(char \*path, int mode);
* int	 open(char \*path, int flags);
* int	 close(int fd);
* int	 read(int fd, void \*buf, size_t len);
* int	 write(int fd, void *\buf, size_t len);
* int  unlink(char \*path);
* int  lseek(int fd, int hi_off, int lo_off, int how);

*Note: The header file <unistd.h> is empty except for `#include <stdlib.h>`*

Stdio Library
-------------
**The following functions are supported in the ElfC stdio C library.**

**Unbuffered Character I/O**

* char \*gets(char \*buf);
* int	 puts(const char \*s);
* int	 putstr(const char \*s);
* int getch(void);
* int	putch(int ch);

*Note: putstr is similar to puts(), but it does not add a newline after the string.*

**Buffered Character I/O**

* int fgetc(FILE \*f);
* int fputc(int c, FILE \*f);
* char \*fgets(char \*s, int len, FILE \*f);
* int fputs(const char \*s, FILE \*f);
* int putchar(int c);
* int getchar(void);
* int ungetc(int c, FILE \*f);

*Note: all stdio functions, except the Unbuffered Character I//O functions, support a one byte push-back buffer through the ungetc() function.*

**Buffered File I/O**

* FILE \*fdopen(int fd, int iomode);
* int fclose(FILE \*f);
* FILE \*fopen(const char \*path, const char \*mode);
* size_t fread(void \*p, size_t size, size_t count, FILE \*f);
* size_t fwrite(const void \*p, size_t size, size_t count, FILE \*f);
* int fflush(FILE \*f);

*Note: Elf/OS and Mini/DOS use a write through buffer, so the fflush function is implemented as a NOP (No Operation) function*

**Formatted Output**

* int fprintf(FILE \*f, const char \*fmt, ...);
* int printf(const char \*fmt, ...);
* int sprintf(char \*buf, const char \*fmt, ...);
* int kprintf(int fd, const char \*fmt, ...);
* int vfprintf(FILE \*f, const char \*fmt, void \*\*args);
* int vprintf(const char \*fmt, void \*\*args);
* int vsprintf(char \*buf, const char \*fmt, void \*\*args);

*Note: Information about supported print conversions can be found on the [ELFC Detailed Information](ELFC.md) page.*

**Formatted Input**

* int fscanf(FILE \*f, const char \*fmt, ...);
* int scanf(const char \*fmt, ...);
* int sscanf(char \*src, const char \*fmt, ...);

*Note: Information about supported scan conversions can be found on the [ELFC Detailed Information](ELFC.md) page.*

**File Operations**

* int remove(const char \*path);
* int rename(const char \*old, const char \*new);
* char \*tmpnam(char \*buf);
* FILE \*tmpfile(void);

*Notes:*
* *`tmpnam` creates a filename such as `temp.00`.*
* *`tmpfile` creates temporary file using a name generated by `tmpnam`.*
* *Files created by `tmpfile` are deleted when closed by `fclose`.*

**File Position Functions**

* int fgetpos(FILE \*f, pos_t \*pos);
* int fsetpos(FILE \*f, pos_t \*pos);
* int fseek(FILE \*f, int offset, int how);
* int ftell(FILE \*f);

**File Error Functions**

* int ferror(FILE \*f);
* int feof(FILE \*f);
* void clrerror(FILE \*f);
* void perror(const char \*msg);

String Library
----------------

**The following functions are supported in the ElfC string C library.**

**Memory Functions**

* void \*memchr(const void \*p, int c, size_t n);
* int memcmp(const void \*p1, const void \*p2, size_t n);
* void \*memcpy(void \*d, const void \*s, size_t n);
* void \*memmove(void \*d, const void \*s, size_t n);
* void \*memset(void \*p, int c, size_t n);

**String Functions**

* char \*strcat(char \*d, const char \*a);
* char \*strchr(const char \*s, int c);
* int strcmp(const char \*s1, const char \*s2);
* char \*strcpy(char \*d, const char \*s);
* size_t strcspn(const char \*s, const char \*set);
* char \*strdup(const char \*s);
* char \*strerror(int err);
* size_t strlen(const char \*s);
* char \*strncat(char \*d, const char \*a, size_t n);
* int strncmp(const char \*s1, const char \*s2, size_t n);
* char \*strncpy(char \*d, const char \*s, size_t n);
* size_t strlcpy(char \*d, const char \*s, size_t n);
* char \*strpbrk(const char \*s, const char \*set);
* char \*strrchr(const char \*s, int c);
* size_t strspn(const char \*s, const char \*set);
* char \*strstr(const char \*s1, const char \*s2);
* char \*strtok(char \*s, const char \*sep);

*Note: `strlcpy` is similar to `strncpy`, except it always copies a null and it does not zero pad.*

Ctype Library
--------------
**The following functions are supported in the ElfC ctype C library.**

**Character Type Functions**

* int	isalnum(int c);
* int	isalpha(int c);
* int	iscntrl(int c);
* int	isdigit(int c);
* int	isgraph(int c);
* int	islower(int c);
* int	isprint(int c);
* int	ispunct(int c);
* int	isspace(int c);
* int	isupper(int c);
* int	isxdigit(int c);
* int	tolower(int c);
* int	toupper(int c);


Assert Library
--------------

**The following function is supported in the ElfC assert C library.**

* void assert(int a, char\* file, int line);

*Notes:*
* *`assert` is implemented by a function, rather than a macro, because preprocessor macros do not support parameters.*
* *The pre-defined macros `__FILE__` and `__LINE__` should be used for the file and line arguments.*
* *If the macro `NDEBUG` is defined then the assert function returns immediately*
* *Otherwise, `assert` prints a message containing the file name and line number and then calls the `abort` function to exit.*

Stdarg Library
---------------

**The following functions are supported in the ElfC stdarg C library.**

* void	\*\*_va_start(void \*last);
* void	 \*_va_arg(void \*\*ap);
* void	  _va_end(void \*\*ap);

*Notes:*
* *The `stdarg` library is implemented by functions, because preprocessor macros do not support parameters.*
* *The `va_arg` function does not include an argument for the type.*
* *The `va_end` function is a NOP (No Operation) function.*

More information about unsupported library functions, header files and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.


Time Library
-------------

**The standard C time structure tm is defined by the ElfC time C library.**
```
struct tm {
    int tm_sec;       /* seconds after the minute (0 to 60) */
    int tm_min;       /* minutes after the hour (0 to 60) */
    int tm_hour;      /* hours after midnight (0 to 23) */
    int tm_mday;      /* day of the month (1 to 31) */
    int tm_mon;       /* months since January (0 to 11) */
    int tm_year;      /* years since 1900 */
    int tm_wday;      /* days since Sunday (0 to 6) */
    int tm_yday;      /* days since January 1 (0 to 365) */
    int tm_isdst;     /* Daylight Savings Time (0 => no, 1 => yes, -1 => unknown) */
};
```

**The following functions are supported in the ElfC time C library.**

* int  systime(struct tm \*tp);
* char \*asctime(struct tm \*tp);
* char \*cstime(void);
* int  strftime(char \*s, int smax, const char \*fmt, struct tm \*tp);
* void timezone(char \*tzname, int tzoff_min, int tzdst);
* int  utctime(struct tm \*tp);

*Notes:*
* Elf/OS v5 and Mini/DOS do not provide API for the time_t or clock_t variables nor is there support for timezone information, but they do support the current time through kernel API.
* Library functions that provide the clock or system time variables are not supported.
* The ElfC time library supports modified time functions that use the standard C time structure instead of the clock time or system time variables.
* The systime(struct tm \*tp) and utctime(struct tm \*tp) populate a time structure with values obtained from the kernel.
* The ElfC time library provides a timezone function to manually set the locale timezone Information and dst values used by the utctime() and strftim() functions in the C time library.
* The timezone() function should be called before to set the local values before calling other time functions.

More information about unsupported library functions, header files and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.

Next Release
-------------

* Update the preprocessor to handle Macro parameters.
* Add support to the preprocessor to accept multi-line commands.
* Add support to the preprocessor for the `#` and `##` operators.

Future Goals
-------------

* Convert library to 32-bit library and implement long, short and float data types.
* Convert the rand function in stdlib to use inline assembly code.
* Upgrade the expression stack logic to handle 32-bit data types like long and float.
* Implement double keyword as synonym for float
* Implement the C math library.
* Create a native Elf/OS (and Mini/DOS) version of ElfC that uses the native Asm/02 and Link/02 programs.


Differences Between ElfC and Full C89
-------------------------------------

*  The following keywords are not recognized:
   `double`, `float`, `long`, `short`.

*  There are four primitive data types: signed and unsigned `int` and
   signed and unsigned `char`; there are also void pointers, and there
   is limited support for `int(*)()` (pointers to functions
   of type int).

*  Arrays are limited to one dimension.

*  Old K&R-style function declarations (with parameter declarations
   between the parameter list and function body) are not
   accepted.

*  Pointers to `const` variables are supported, but neither `const` pointers to
   (varying) variables, nor `const` pointers to `const` variables are supported,
   i.e. `const int * p;` is supported, but `int * const p;` and `const int * const p;`
   are *not* supported.

*  The `const` and `volatile` keywords are ignored for structures and unions, but
   may be used for their members.

*  There are no long integers.

*  Struct/union declarations must be separate from the declarations of
   struct/union objects, i.e. `struct p { int x, y; } q;` will not work.

*  Struct/union declarations must be global (struct and union
   objects may be declared locally, though).

*  No more than two levels of indirection are supported for pointers
   to structures and unions, i.e. pointers to a struct/union and pointers
   to pointers to a struct/union are supported.

*  A struct/union cannot be passed as an argument to a function, but a
   *pointer* to struct/union can be passed as an argument to a function.

*  There is no support for bit fields.

*  Only ints, chars, and arrays of int and char can be
   initialized in their declarations; pointers can be
   initialized with NULL or a constant address value.

*  Local arrays cannot have initializers.

*  The initializer list must have exactly the same elements as the gobal or static
   array.  ElfC will not pad the array, nor will ElfC truncate the initializer list
   or string.

*  Local declarations are limited to the beginnings of function
   bodies (they do not work in other compound statements).

*  Arguments of prototypes must be named.

*  There are no parameterized macros.

*  The `#if` and `#elif` preprocessor commands are not recognized.

*  The preprocessor does not accept multi-line commands.

*  The preprocessor does not accept comments in (some) commands.

*  The preprocessor does not recognize the `#` and `##` operators.

*  There may not be any blanks between the `#` that introduces
   a preprocessor command and the subsequent command (e.g.:
   `# define` would not be recognized as a valid command).

*  The `sizeof` operator requires parentheses.

*  Subscripting an integer with a pointer (e.g. `1["foo"]`) is
   not supported.

*  Function pointers are limited to one single type, `int(*)()`,
   and they have no argument types. Note that this declaration
   will in fact generate a pointer to `int(*)(void)`.

*  Pointers to function pointers are not supported.

*  Due to the lack of parameterized macros, `assert` and other
   macros are implemented as functions.

*  The SubC compiler accepts `//` comments in addition to `/* */`.


Repository Contents
-------------------

* **/src/elfc**  -- Source files for compiling ElfC.
  * MakeElfC - Windows nmake file to compile source files. Use the command *nmake -f MakeElfC* to compile the elfc.exe file.  The command *nmake -f MakeElfC clean* will remove generated files before compiling.
  * Makefile - Linux make file to compile source files. Use the command *make* to compile the elfc.exe file.  The command *make clean* will remove generated files before compiling.
* **/src/examples** -- Example C files
  * hello.c -- Classic C "Hello, World" example
  * datetime.c -- Demo of various time and date format conversions
  * fib.c -- Demo to print series of Fibonacci numbers
  * printfmt.c -- Demo of various printf format conversions
  * scanfmt.c -- Demo of various scanf format conversions
* **/src/clib**  -- Source files for compiling ElfC C libraries
* **/src/clib/include**  -- Common include files for compiling ElfC C libraries
* **/src/clib/lib**  -- Compiled ElfC C Library files
* **/src/clib/elfc**  -- Source files for elfc.lib library
  * clean.bat - Windows batch file to clean binaries before assembling.
  * build.bat - Windows batch file to assemble files into elfc.lib system library.
  * Makefile - Linux make file to compile source files.
* **/src/clib/crt0**  -- Source files for ElfC runtime start-up library
* **/src/clib/stdlib**  -- Source files for ElfC stdlib C library
* **/src/clib/stdio**  -- Source files for ElfC stdio C library
* **/src/clib/string**  -- Source files for ElfC string C library
* **/src/clib/ctype**  -- Source files for ElfC ctype C library
* **/src/clib/stdarg**  -- Source files for ElfC stdarg C library
* **/src/clib/assert**  -- Source files for ElfC assert C library
* **/src/tests**  -- Functional test files for ElfC
  * ptest1.c to ptest5.c  -- Functional tests for pointer and array arithmetic
  * libtest1.c to libtest4.c  -- Functional tests for various library functions
  * filetest1.c to filetest5.c  -- Functional tests for buffered file functions
* **/bin**  -- Binary files for ElfC
  * elfc_r304.zip** -- A zip file with the Windows version of the Release 3.04 ElfC binary files, include files and library files. To install ElfC, unzip this file into the desired directory.
  * elfc.arm65.tar.gz** -- A tar file with the Arm64 Linux version of the Release 3.04 ElfC binary files, include files and library files. To install ElfC, unpack this file into the desired directory.
  * elfc.linux_64.tar.gz** -- A tar file with the Windows version of the Release 3.04 ElfC binary files, include files and library files. To install ElfC, unpack this file into the desired directory.
* **/sample** -- Sample code for the walk-through documentation (TBD)

Acknowledgements
-----------------

Kudos to Tony Hefner for contributing the Linux builds, the Linux make files, and adding support for Cmake.

A big thank-you to David Madole for his suggestions to improve code performance, including designing a sub-routine scheme that doubled the code performance.

Many thanks to Mike Riley for making his library code available and his patience in answering my questions.

A debt of gratitude to Nils Holms for his excellent book, Practical Compiler Construction and for creating SubC, which provides the basis for ElfC.

Thanks to everyone in the [Cosmac Elf Group](https://groups.io/g/cosmacelf/topics) for their feedback, comments and suggestions, and most of all for their encouragement.


License Information
-------------------

This code is public domain under the MIT License, but please buy me a beverage
if you use this and we meet someday (Beerware).

References to any products, programs or services do not imply
that they will be available in all countries in which their respective owner operates.

Any company, product, or services names may be trademarks or services marks of others.

All libraries used in this code are copyright their respective authors.

The assembly code is based on a Elf/OS code libraries written by Mike Riley and assembled with the Asm/02 assembler and liked with the Link/02 linker written by Mike Riley.

The C code is based on the SubC compiler written by Nils M Holms and compiled with Microsoft Visual Studio 2022 C compiler.

Practical Compiler Construction, A No-nonsense Tour through a C Compiler was written by Nils M Holms and published by Lulu Press, 2022 (2nd Ed.)

Source code for the SubC Compiler
Copyright (c) 2011-2016 by Nils M Holm
Placed in the public domain by the author.

Elf/OS
Copyright (c) 2004-2025 by Mike Riley

Mini/DOS
Copyright (c) 2025-2025 by David Madole

Asm/02 1802 Assembler
Copyright (c) 2004-2025 by Mike Riley

Link/02 1802 Linker
Copyright (c) 2004-2025 by Mike Riley

Library/02 Elf/OS standard library
Copyright (c) 2022-2025 by Mike Riley

Microsoft Visual Studio 2022
Copyright (c) 2022-2025 by Microsoft Corp.

Many thanks to the original authors for making their designs and code available as open source.

This code, firmware, and software is released under the [MIT License](http://opensource.org/licenses/MIT).

The MIT License (MIT)

Copyright (c) 2025 by Gaston Williams

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

**THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.**
