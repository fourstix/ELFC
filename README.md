# ELFC
A C compiler for a CDP1802 based microcomputer running Elf/OS or Mini/DOS.  ElfC is based on SubC written by Nils M Holms.

Design Goals
-------------
* Use the Elf/OS [Asm/02](https://github.com/fourstix/Asm-02) assembler and [Link/02](https://github.com/fourstix/Link-02) linker to produce CDP1802 binary code to run as an Elf/OS or Mini/DOS program
* Create a library based on Mike Riley's [Library/02](https://github.com/rileym65/Library-02) standard library.
* Target both Elf/OS and Mini/DOS as a platform.
* Target Windows as the development platform (cross-compiler)
* Use an expression stack similar to the one implemented in Mike Riley's Fortran/02 program.
* Minimize changes to basic SubC compiler code and prefer changes to the code generation and library code functions.
* Implement the code generation functions first, migrate to the latest version of SubC and then work on implementing the C libraries. 
 
Release 1
----------

This version is based on the [SubC book version, 2nd Ed.](https://www.t3x.org/subc/README-2nd-ed.html) described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms.  

I strongly recommend reading Nils's book.  Practical Compiler Construction is a very good guide in explaining the theory behind the SubC compiler as well as describing the compiler's code.  The second edition can be ordered as a [paperback](https://www.lulu.com/en/us/shop/nils-m-holm/practical-compiler-construction/paperback/product-179kp29q.html) or [pdf ebook file](https://www.lulu.com/en/us/shop/nils-m-holm/practical-compiler-construction/ebook/product-18knr78q.html) from Lulu press.

In Release 1 the code generation functions for Elf/OS have all been implemented.  The arithmetic and logical operators have all been implemented and tested.


Release 2
----------
This release migrates the code base to the current [Experimental SubC](https://www.t3x.org/subc/index.html) version so that the code generator can include structures, unions and typedefs.

This release supports some basic code optimization as described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms

The compiler supports the [Asm/02]((https://github.com/fourstix/Asm-02)) and [Link/02]((https://github.com/fourstix/Link-02) linker better, and included files and libraries are better organized.

The C runtime module `crt0` now holds the start-up code for the program.  The start up code now pushes the expected command line arguments for `main` onto the stack (`int argc` and `char **argv`) and then calls the main function.

An additional compiler option `-L` will compile and assemble Elf/OS library modules from C files.  

Overview
--------

* Version 2 implements the code generation functions required to compile a C file and assemble the resulting CDP1802 assembly and link code files into a binary program for the Elf/OS (or Mini/DOS) operating system.  

* The assembler [Asm/02]((https://github.com/fourstix/Asm-02)) and linker [Link/02](https://github.com/fourstix/Link-02) are now invoked with the same path as the compiler.  The C library files and header files are located in the same manner, so that the preprocessor commands `#include <header.h>` and `#include "header.h"` work as expected.

* Version 2 extends the library of arithmetic and variable functions based on the Elf/OS 16-bit standard library [Library/02](https://github.com/rileym65/Library-02) to manipulate values on an expression stack.

* This version implements the changes to the book compiler code contained in the latest current [Experimental version of SubC](https://www.t3x.org/subc/index.html).  

* The peep-hole code optimizations are all implemented except for the 386 assembly code Type optimizations which have no equivalents in 1802 assembly code.  In addition, jump optimizations and push / pop optimizations were added that are specific to 1802 assembly code.  Constant folding and AST trees are supported as in the [Experimental SubC](https://www.t3x.org/subc/index.html) code.

* The `#pragma` preprocessor directive can be used to directly insert a line of assembly code into the generated assembly file as well as the the asm() statement.

* The `__LINE__` and `__FILE__` preprocessor directives were implemented in this version.

* The arguments `int argc` and `char **argv` are now available as arguments to main.  Up to eight arguments are supported.  The argument `argv[0]` points to the command string that invoked the program.

* Skeleton libraries for `stdio.lib` and `stdlib.lib` were created in Version 2 as a proof of concept.

* The ElfC compiler now accepts inline comments (`// comments`) as well as traditional C commments (`/* comments */`).

* `struct`, `union` and `typedef` are now supported.

* `&array` is now valid syntax (you no longer have to write
   `&array[0]`).

* The `auto`, `register`, and `volatile` keywords are recognized
   (as no-ops). 

* `enum`'s may now be local.

* `extern` identifiers may now be declared locally.

* Prototypes may have the `static` storage class.

* The `#error`, `#line`, and `#pragma` commands have been added.

* A broader subset of C expression syntax is accepted in constant expression contexts. Pointer variables can be initialized with NULL. 

Library Compiler Option 
------------------------

* The new `-L` ElfC option will compile and assemble a C source file into a prg file defining an Elf/OS library procedure.

* The source file should contian a public function with same name as the file name of the C file. If no public function in the matches the file name, an error will be generated.

* The procedure name will be the file name with the C prefix and serve as the pubic entry point for the procedure function.

* If needed, the compiler will emit an immediate jump to the public function with the same name as the procedure.

* The entry point function's public name will be suppressed to prevent duplication of the procedure name when linking.

* The prg can then be incorporated into an Elf/OS library.

* The file can contain public functions and public labels. These will be available in the procedure, along with the procedure function name.

* An Elf/OS library is created by concatenating multiple procdure prg files.

Example:

The C file `abs.c`:
```
int abs(int n) {
  return (n < 0) ? -n : n;
  }
```
Compiled with:
```
..\elfc -L abs.c
```
This will produce the file abs.prg that can be concatenated into an Elf/OS library, such as stdlib.lib. The library can then be linked to a C program to provide the `abs()` function.  
```
type abort.prg abs.prg exit.prg > stdlib.lib 
```


Next Release
-------------

* Implement the basic set of C libraries and header files as described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms. 

* The C libraries should be created from C files using the ElfC (`-L`) library compile option.

* The header files should use `#pragma` statements so the libraries link properly.

* Implement the va_args mechanism described in the book [Practical Compiler Construction](https://www.t3x.org/reload/index.html) by Nils M Holms. 

* Implement the `atexit()` mechanism

* Implement time functions compatible with Elf/OS (Mini-DOS) kernel and BIOS API.

Future Goals
-------------

* Convert library to 32-bit library and implement long and float data types. 
* Upgrade the expression stack logic to handle 32-bit data types like long and float.
* Implement double keyword as synonym for float
* Implement the C math library.
* Implement signed and unsigned data types.
* Create a native Elf/OS version of ElfC that uses the native Asm/02 and Link/02 programs in Elf/OS.  


Differences Between SubC and Full C89
-------------------------------------

*  The following keywords are not recognized:
   `const`, `double`, `float`, `goto`, `long`, `short`,
   `signed`, `unsigned`.

*  There are only two primitive data types: the signed `int` and
   the unsigned `char`; there are also void pointers, and there
   is limited support for `int(*)()` (pointers to functions
   of type int).

*  No more than two levels of indirection are supported, and
   arrays are limited to one dimension, i.e. valid declarators
   are limited to `x`, `x[]`, `*x`, `*x[]`, `**x` (and `(*x)()`).

*  K&R-style function declarations (with parameter declarations
   between the parameter list and function body) are not
   accepted.

*  There are no `const` variables.

*  There are no unsigned integers, long integers, or signed
   chars.

*  Struct/union declarations must be separate from the
   declarations of struct/union objects, i.e.
   `struct p { int x, y; } q;` will not work.

*  Struct/union declarations must be global (struct and union
   objects may be declared locally, though).

*  There is no support for bit fields.

*  Only ints, chars, and arrays of int and char can be
   initialized in their declarations; pointers can be
   initialized with 0 or NULL.

*  Local arrays cannot have initializers.

*  Local declarations are limited to the beginnings of function
   bodies (they do not work in other compound statements).

*  Arguments of prototypes must be named.

*  There is no `goto`.

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

*  There is no `assert()` due to the lack of parameterized macros.
   
*  The SubC compiler accepts `//` comments in addition to `/* */`.

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

Mini-DOS 
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
