# ELFC
A C compiler for a CDP1802 based microcomputer running Elf/OS or Mini/DOS.  ElfC is based on SubC written by Nils M Holms.

Documentation
---------------
* ELFC General Information (This Page)
* [ELFC Detailed Information](ELFC.md)
* [ELFC Internal Information](INSIDE.md)

Installation
-------------
* Unzip the file elfc_r361.zip into the desired directory
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

More information about unsupported library functions and header files can be found on the [ELFC Detailed Information](ELFC.md) page.  Information about ElfC internals can be found on the [ELFC Internal Information](INSIDE.md) page.

Release 2.5
------------

This release adds an implementation of the C time library to ElfC, and a compiler option `-N` to compile without linking the C stdlib and stdio libraries.

More information about the time library functions and header files can be found on the [ELFC Detailed Information](ELFC.md) page.  Information about ElfC internals can be found on the [ELFC Internal Information](INSIDE.md) page.

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

* The `varargs` mechanism is now supported as functions as described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms. (Starting with version 3.3, the standard C mechanism for `varargs` is supported.)

* The `assert` macro is implemented as a function with support for the `NDEBUG` macro. (Starting with version 3.3, the standard C mechanism for the `assert` macro is supported.)

* STG ROM break points are supported by the `_STGROM_` and `BRKPT` macros.

* A broader subset of C expression syntax is accepted in constant expression contexts. Pointer variables can be initialized with NULL.

More information about unsupported library functions and header files can be found on the [ELFC Detailed Information](ELFC.md) page. Information about ElfC internals can be found on the [ELFC Internal Information](INSIDE.md) page.


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

* The included files were cleaned up to eliminate unused definitions, and the kernel api were moved to a separate included file.

More information about Version 3, signed and unsigned types and library functions can be found on the [ELFC Detailed Information](ELFC.md) page.  Information about ElfC internals can be found on the [ELFC Internal Information](INSIDE.md) page.

Release 3.1
------------
*  This release removes the restriction of only 2 levels of pointer indirection and supports up to 15 levels of indirection. This meets the ANSI specified minimum of 12 levels of indirection.

* This release adds support for local labels and the `goto` keyword.

* The `const` keyword is now supported.

* Functions may now return a structure or union.

* Structures and unions may now be assigned.

* ElfC can now emit warning messages when compiling code.

* Pointers may now be initialized with non-zero constant address values, like *0xFF00*

* The `__FUNC__` preprocessor directive was renamed to `__FUNCTION__` in this version.

* Declaring a variable as `volatile` will now prevent optimizations on that variable.

* Static (and global) arrays may be initialized using an initializer list or a string. ElfC will emit an error message if the initializer list size does not match the size of the array.

More information about Version 3.1, labels, `goto`, `volatile` and `const` keywords and library functions can be found on the [ELFC Detailed Information](ELFC.md) page.  Information about ElfC internals  can be found on the [ELFC Internal Information](INSIDE.md) page.

Release 3.3
-----------

Release 3.3 adds support for parameterized macros.  The ElfC preprocessor meets the requirements of the ANSI C89/C90 specification.

* The preprocessor can now handle macros with parameters.
* The preprocessor supports macros with empty parameter lists.
* The preprocessor can accept multi-line macro commands.
* The preprocessor supports the `#`(stringify) and `##` (paste token) operators.
* The scanner now supports line splicing where a backslash at end of line indicates line continuation.
* The stdarg and assert libraries are replaced by the traditional C macros.
* The abs, min and max functions in the stdlib library and the getchar, putchar, getc and putc in the stdio library are replaced by their traditional C macros.

Compiler Option Changes
-----------------------
* The `-P` option will cause ElfC to output the macro text to stdio as each macro is expanded.

Release 3.4
-----------

Release 3.4 adds support for initializations and 32-bit integer math, as well as support for file sizes larger than 32K and various bug fixes.

* Ints, chars, and arrays of int and char can be initialized in their declarations.
* Pointers can be initialized with NULL or a constant address value.
* Character pointers can be initialized with the address of a static string.
* Dynamic local initializations are now supported.  Initializations such as 'int len = strlen(x);' are now supported.
* Local array initializations are supported.
* Character arrays may be initialized by a string or by a list of character constants.
* Character pointers may be initialized by a string.
* Initializations for an array may define fewer elements than the array.
* Static initializations are now padded with zeros.
* The Math32 library, contributed by Tony Hefner, adds support for 32-bit integer arithmetic.
* The lseek32 and fseek32 functions provide support for file sizes up to 2GB, by using the Math32 library. (Thanks to Tony Hefner)
* The fsetpos and fgetpos functions now use the Math32 library to support file sizes up to 2GB. (Thanks to Tony Hefner)
* The scanner no longer accepts integer literals that are greater than the largest possible 16-bit integer value of 65535.
* ElfC supports the suffixes 'u' or 'U' to indicate an integer literal is an unsigned value.
* The scanner will issue a warning if an integer literal is larger than the maximum signed value, unless the integer literal has the unsigned suffix.
* Error number values were aligned with POSIX values.
* A bug was fixed in the left-shift operation. (Thanks to Tony Hefner)
* Assignments from a struct/union pointer to a struct/union variable now work correctly. The pointer to struct/union is now dereferenced correctly.
* Breakpoints can now be configured for any ROM address.

More information about Version 3.4 and library functions can be found on the [ELFC Detailed Information](ELFC.md) page.  Information about ElfC internals can be found on the [ELFC Internal Information](INSIDE.md) page.

Release 3.5
-----------

Release 3.5 adds support for passing structures and unions by value to a function and adds support for several POSIX functions to the string library.  A new compiler option `-M` supports smaller memory size versions of stdlib and stdio, named elfstd and elfio. In addition to these features, several issues found during self-compiling ElfC were fixed in this release.

New Features
-------------
* Structures and unions may be passed by value as an argument to the function.
* A struct/union argument may be used as the return value of a function.
* Several additional functions were added to the string library.
* Some parameters for name length and number of arguments were increased to meet additional ANSI C89/C90 minimum translation limits.
* An additional debug option `-d tree` was added to the compiler to support debugging AST trees and optimizations.
* A walkthrough of ElfC compilation process and its output files is documented on the [ELFC Internal Information](INSIDE.md) page.
* Details about the ElfC stack frame layout was documented with examples on the [ELFC Internal Information](INSIDE.md) page.
* The functions in the Math32 library were converted to pass 32-bit numbers by value.
* Smaller memory versions of stdlib and stdio libraries, named elflib and elfio, are available through the `-M` compiler option.
* The elfstd library provides the same functions as stdlib, but uses the Elf BIOS, when possible, rather than C library code.
* The elfio libraries provides fewer print formatting and scanning options, but are otherwise compatible with stdio and stdlib. (See the [ELFC Detailed Information](ELFC.md) page for details.)
* The ctype library was re-written to provide the same functions with smaller library code.
* Upgraded Asm/02 to the latest version.
* ElfC can now self-compile, but the object code files created are too large for the linker Link/02 to link and resolve.
* Added macro `__ELFIO__` that is defined when `-M` is used.

Issues Fixed
-------------
* MIN and MAX macros should be capitalized.
* Array of structures falsely considered as constant.
* Enum value failed in first case of switch statement.
* Zero was not treated as NULL when assigned to pointer.
* Macro preprocessor did not properly handle parenthesis inside strings and character literals.
* Updated modpath logic to compile with ElfC.
* Scanner did not terminate correctly after syntax error.
* Structure pointer was not correctly de-referenced when used as argument to function.
* ElfC could emit strings too long for Asm/02 assembler.
* Character types cast to to int or unsigned int, now yield the expected values.
* Fixed a bug where unsigned operations were not always propagated in arithmetic and logic expressions.
* Fixed a bug in the elfstd library version of itoa.
* Fixed errors in time library when `-M` option was used.
* Fixed a problem with %s print format option when `-M` option was used.

Compiler Option Changes
-----------------------
* The `-d tree` option will cause ElfC to output information about the AST tree as it compiles.
* The `-M` option will cause ElfC to use smaller memory versions of the stdlib and stdio libraries, named elflib and elfio.

*Note: Information about supported print and scanning conversions can be found on the [ELFC Detailed Information](ELFC.md) page.*


Release 3.6
-----------

Release 3.6 adds support for multi-dimensional arrays to ElfC. Release 3.6 contains a new version of the 32-bit integer math library completely overhauled by Tony Hefner to improve performance, and ElfC now supports initializing arrays of pointers.

New features
------------

* ElfC supports multi-dimensional arrays, e.g. `int a[3][4];` is now supported.
* ElfC supports typedefs with array types.
* ElfC supports passing multi-dimensional array to functions and supports pointer decay.
* ElfC allows references to arrays to be assigned to pointers that match the base type through pointer decay.
* ElfC now allows any pointers that point to the same base type to be assigned, even if the levels of indirection are different.s
* ElfC will issue a warning if the pointer levels of indirection are different, but will still allow the assignment.
* The 32-bit integer math library was re-written by Tony Hefner to improve performance. Many thanks to Tony for this contribution.
* Three new example programs, a calculator, a fractal generator and a 400 digits of pi calculation,  were added by Tony Hefner to demonstrate the use of the 32-bit integer math library.  Again, Kudos to Tony for creating these examples.
* An array of character pointers can now be initialized by a list of strings, e.g. `char *birds[] = {"crow", "hawk", "owl", "robin"};`
* Arrays of other pointer types can be initialized with a list of integer constants.

Issues Fixed
-------------

* ElfC interprets Section 6.3.16.1 of the ANSI C89/C90 specification to allow the pointers to be assignable when they both point to the same basic type, even if they have different levels of indirection.  (Section 6.3.16.1 is considered ambiguous on this point by some.)
* ElfC allows this assignment in accordance with future versions of the specification, C99 and C11, that explicitly state that this assignment should be allowed.

*Note: Information about multi-dimensional arrays and pointer decay can be found on the [ELFC Detailed Information](ELFC.md) page.*

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
* off_t lseek32(int fd, off_t *offset, int whence);

*Notes:*
* The header file <unistd.h> is empty except for `#include <stdlib.h>` *
* The type `off_t` is an int32 structure used by the Math32 library *

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
* int fseek32(FILE* f, off_t *offset, int whence);
* int ftell(FILE \*f);

*Note: The type `pos_t` is an int32 structure used by the Math32 library*

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
* char \*strerror(int err);
* size_t strlen(const char \*s);
* char \*strncat(char \*d, const char \*a, size_t n);
* int strncmp(const char \*s1, const char \*s2, size_t n);
* char \*strncpy(char \*d, const char \*s, size_t n);
* char \*strpbrk(const char \*s, const char \*set);
* char \*strrchr(const char \*s, int c);
* size_t strspn(const char \*s, const char \*set);
* char \*strstr(const char \*s1, const char \*s2);
* char \*strtok(char \*s, const char \*sep);

**POSIX Functions**
* int strcasecmp(const char \*s1, const char \*s2);
* char \*strcasestr(const char \*s1, const char \*s2);
* char \*strdup(const char \*s);
* size_t \*strlcat(char \*d, const char \*s, size_t n);
* size_t strlcpy(char \*d, const char \*s, size_t n);
* char \*strlwr(char \*str)
* int strncasecmp(const char \*s1, const char \*s2, size_t n);
* char \*strndup(const char \*s, size_t n);
* size_t strnlen(const char \*s, size_t n);
* char \*strnstr(const char \*s1, const char \*s2, size_t n);
* char \* strrev(char \*s);
* char \*strsep(char \*\*str, const char \*sep);
* char \*strupr(char \*str);
* char \*strim(char \*str);

*Notes:*
* `strlcpy` is similar to `strncpy`, except it always copies a null and it does not zero pad.
* `strlcat` is similar to `strncat`, except it always copies a null, so up to *(l-1).* characters are concatenated.
* `strcasecmp`, `strncasecmp` and `strcasestr` are case *insensitive* comparisons.

More information about the additional POSIX string functions can be found on the [ELFC Detailed Information](ELFC.md) page.



Ctype Library
--------------
**The following functions are supported in the ElfC ctype C library.**

**Character Type Functions**

* int	isalnum(int c);
* int	isalpha(int c);
* int	isascii(int c);
* int	isblank(int c);
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


Assert Header
--------------

**The assert macro is provided by the <assert.h> header file**

* assert(int *expression*);

*Notes:*
* If *expression* evaluates to false (zero), the `assert` macro prints a message to `stderr` containing the file name and line number and then calls the `abort` function to exit.*
* *If the macro `NDEBUG` is defined then the assert macro is ignored*

Stdarg Header
--------------
 Macros in the <stdarg.h> header file support stepping through a list of function arguments of variable numbers and type.

* va_start(va_list ap, lastarg);
* va_arg(va_list ap, type);
* va_end(va_list ap);

More information about unsupported library functions, header files, macros and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.


Time Library
-------------

**The standard C time structure tm is defined by the ElfC time C library.**
```c
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


Math32 Library
--------------
**The math2 library functions use the following structure and type.**

```c
struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

/* 32-bit number represented as two 16-bit values */
typedef struct int32 int32_t;
```

**The following functions are supported in the ElfC math32 library.**

* int32_t absi32(int32_t n);
* int32_t addi32(int32_t a, int32_t b);
* int32_t subi32(int32_t a, int32_t b);
* int32_t muli32(int32_t a, int32_t b);
* int32_t muli32x16(int32_t a, int b);
* int cmpi32(int32_t a, int32_t b);
* int32_t shli32(int32_t a);
* int32_t shri32(int32_t a);
* int32_t asri32(int32_t a, int n);
* int32_t divi32(int32_t a, int32_t b, int32_t \*rem);
* int32_t toit32(int n);
* int32_t negi32(int32_t n);
* int32_t atoi32(const char \*str);
* char \*i32toa(int32_t n, char \*str);
* int32_t strtoi32(const char \*nptr, char \*\*endptr, int base);

More information about unsupported library functions, header files and ElfC internals can be found on the [ELFC Detailed Information](ELFC.md) page.

Next Release
-------------
* Initialization for structure objects
* Implement a 32-bit library with float data types.
* Convert the rand function in stdlib to use inline assembly code.

Future Goals
-------------
* Implement a version of the C math library to use the float data types.
* Create a native OS (Elf/OS or Mini/DOS) versions of the Asm/02 and Link/02 programs using ELFC.
* Create a native OS (Elf/OS or Mini/DOS) version of ElfC that uses the native Asm/02 and Link/02 programs.


Differences Between ElfC and Full C89
-------------------------------------

*  The following keywords are not recognized:
   `double`, `float`, `long`, `short`.

*  There are four primitive data types: signed and unsigned `int` and
   signed and unsigned `char`; there are also void pointers, and there
   is limited support for `int(*)()` (pointers to functions
   of type int).

*  There are no 32-bit primitive types. There are no long integers, no doubles, no floats.

*  ElfC does not support declaring a variable as a pointer to an arbitrary array.
   IE, the syntax `int (*) a[];` is not supported.

*  An array type may be declared in a `typedef` or in a variable declaration, but not both.

*  Old K&R-style function declarations (with parameter declarations
   between the parameter list and function body) are not
   accepted.

*  Pointers to `const` variables are supported, but neither `const` pointers to
   (varying) variables, nor `const` pointers to `const` variables are supported,
   i.e. `const int * p;` is supported, but `int * const p;` and `const int * const p;` are *not* supported.

*  The `const` and `volatile` keywords are ignored for structures and unions, but
   may be used for their members.

*  Struct/union definition declarations must be separate from the declarations of
   struct/union objects, i.e. `struct p { int x, y; } q;` will not work.

*  Struct/union definition declarations must be global (struct and union
   objects may be declared locally, though).

*  Struct/union definition declarations cannot be nested, but struct/union object declarations can be nested.

*  No more than two levels of indirection are supported for pointers
   to structures and unions, i.e. only pointers to a struct/union and pointers
   to pointers to a struct/union are supported.

*  Initialization of a struct/union is not supported.

*  Initialization lists do not support mixed types and cannot be nested.

*  Character arrays must be large enough to accept the entire initialization string plus
   its terminating NULL. ElfC will not silently remove the NULL at the end of an
   initialization string, when the string is one character too long for an array.

*  There is no support for bit fields.

*  Local declarations are limited to the beginnings of function
   bodies (they do not work in other compound statements).

*  Arguments of prototypes must be named.

*  The `#if` and `#elif` preprocessor commands are not recognized.

*  The preprocessor does not accept comments in (some) commands.

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

*  The SubC compiler accepts `//` comments in addition to `/* */`.

*  ElfC supports most, but not all, of the Translation Limits as defined
   by the ANSI C89/C90 specification, Section 5.2.4.1. Details can be
   found on the [ELFC Internal Information](INSIDE.md) page.

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
  * tqdemo.c -- Demo of type qualifiers `volatile` and `const`
  * macros.c -- Demo of various macro mechanisms
  * vargs.c -- Demo of variable argument mechanisms
  * casting.c -- Demo of showing the results of casting various character and integer values.
  * calc.c -- Demo program of a calculator using the 32-bit integer library.
  * mandel.c -- Demo program to plot a Mandelbrot set using the 32-bit integer library.
  * pi.c -- Demo program to compute pi to 400 digits using the 32-bit integer math library.
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
* **/src/clib/math32**  -- Source files for ElfC Math32 library contributed by Tony Hefner
* **/src/tests**  -- Functional test files for ElfC
  * ptest1.c to ptest5.c  -- Functional tests for pointer and array arithmetic
  * libtest1.c to libtest5.c  -- Functional tests for various library functions
  * filetest1.c to filetest5.c  -- Functional tests for buffered file functions
  * math32test.c -- Functional tests for the math32 library functions
  * stctest.c -- Functional tests for structures/union functions
  * arrtest.c -- Functional tests for multi-dimensional arrays
* **/bin**  -- Binary files for ElfC
  * **elfc_r361.zip** -- A zip file with the Windows version of the Release 3.5.6 ElfC binary files, include files and library files. To install ElfC, unzip this file into the desired directory.
  * **elfc_r361.arm64.tar.gz** -- A tar file with the Arm64 Linux version of the Release 3.5.6 ElfC binary files, include files and library files. To install ElfC, unpack this file into the desired directory.
  * **elfc_r361.linux_x64.tar.gz** -- A tar file with the Windows version of the Release 3.5.6 ElfC binary files, include files and library files. To install ElfC, unpack this file into the desired directory.

Acknowledgements
-----------------

Kudos to Tony Hefner for contributing the Linux builds, the Linux make files, and adding support for Cmake.

A big thank-you to David Madole for his suggestions to improve code performance, including designing a sub-routine scheme that doubled the code performance.

Many thanks to Mike Riley for making his library code available and his patience in answering my questions.

Another big shout out to thank Tony Hefner for developing and contributing the Math32 library and for adding support to stdio and stdlib libraries to support file sizes greater than 32K, up to 2GB.

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
Copyright (c) 2004-2026 by Mike Riley

Mini/DOS
Copyright (c) 2025-2026 by David Madole

Asm/02 1802 Assembler
Copyright (c) 2004-2026 by Mike Riley

Link/02 1802 Linker
Copyright (c) 2004-2026 by Mike Riley

Library/02 Elf/OS standard library
Copyright (c) 2022-2026 by Mike Riley

Microsoft Visual Studio 2022
Copyright (c) 2022-2026 by Microsoft Corp.

Many thanks to the original authors for making their designs and code available as open source.

This code, firmware, and software is released under the [MIT License](http://opensource.org/licenses/MIT).

The MIT License (MIT)

Copyright (c) 2026 by Gaston Williams

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
