# ELFC
A C compiler for a CDP1802 based microcomputer running Elf/OS or Mini/DOS.  ElfC is based on SubC written by Nils M Holms.

Design Goals
-------------
* Use the Elf/OS Asm/02 assembler and Link/02 linker to produce CDP1802 code.
* Create a library based on Mike Riley's Library/02 standard library.
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


Overview
--------
* Implement the code generation functions required to compile a C file and generate a CDP1802 assembly code file for the Elf/OS (or Mini/DOS) operating system.  

* Create a library of arithmetic and variable functions based on the Elf/OS 16-bit standard library [Library/02](https://github.com/rileym65/Library-02) to manipulate values on an expression stack.

* Implement the minimal changes to the book compiler code required to assemble and link the code to create an Elf/OS program file.

* Implement the asm() statement in C to directly insert assembly code into the generated assembly file.

Next Release
-------------

* Migrate the code base to the current [Experimental SubC](https://www.t3x.org/subc/index.html) version so that the code generator can include structures, unions and typedefs.

* Merge all changes made to Release 1 into Experimental SubC version.

Future Goals
-------------

* Implement standard library and standard I/O C functions.
* Convert library to 32-bit library and implement long and float data types. 
* Upgrade the expression stack logic to handle 32-bit data types like long and float.
* Implement double keyword as synonym for float
* Implement the C math library.
* Implement signed and unsigned data types.
* Create a native Elf/OS version of ElfC that uses the native Asm/02 and Link/02 programs in Elf/OS.  


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
