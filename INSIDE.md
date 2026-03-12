# ElfC Internal Information


Build Walkthrough
------------------

ElfC creates an Elf/OS binary from a C source file using the following build process shown below using the traditional
"Hello World" example file `hello.c`.

*hello.c*
'''
#include <stdio.h>


int main() {
  printf("Hello, World!");
}
'''

*The build process consists of the following three major steps:*

1. The ElfC program compiles the source file `hello.c` and the included header file `<stdio.h>` into the assembly code file `hello.asm`.
2. The ElfC program invokes the Asm/02 assembler to assemble the `hello.asm` file into the `hello.prg` object file.  The assembler creates the assembly list file `hello.lst` and the assembly build file `hello.build`.
3. The ElfC program invokes the Link/02 linker to link the `hello.prg` object file to the runtime startup module file `crt0.prg`and the default C library files `stdlib.lib` and `stdio.lib` to create the Elf/OS binary file `hello.elfos`.  The linker outputs the `hello.lkb` file iwth linker build number, which servers as the version number for the binary program, and the symbol map `hello.sym` with the linked object module and library routine addresses.


<table>
<tr><th>Step</th><th>Input Files</th><th>Description</th><th>Program</th><th>Output FIles</th><th>Description</th></tr>
<tr><td rowspan="2">1</td><td>hello.c</td><td>C Source</td><td rowspan="2">ElfC compiler</td><td rowspan="2">hello.asm</td><td rowspan="2">Assembly Code</td></tr>
<tr><td>stdio.h</td><td>C Header File</td></tr>
<tr><td rowspan="3">2</td><td rowspan="3">hello.asm</td><td rowspan="3">Assembly Code</td><td rowspan="3">Asm/02 assembler</td><td>hello.prg</td><td>Object File</td></tr>
<tr><td>hello.lst</td><td>Assembly Listing</td></tr>
<tr><td>hello.build</td><td>Assembler Build Number</td></tr>
<tr><td rowspan="4">3</td><td>hello.prg</td><td>Object File</td><td rowspan="4">Link/02 linker</td><td>hello.elfos</td><td>Elf/OS binary</td></tr>
<tr><td>crt0.prg</td><td>Runtime Startup Module</td><td rowspan="2">hello.lkb</td><td rowspan="2">Version Number (Linker Build Number)</td></tr>
<tr><td>stdlib.lib</td><td>C Library</td></tr>
<tr><td>stdio.lib</td><td>C Library</td><td>hello.sym</td><td>Symbol Map</td></tr>
</table>

*Notes:*
* The option `-S` will compile to step one. The command `elfc -S` will compile, but not assemble and not link the code.
* The option `-c` will comiple and assemble to step two.  The command `elfc -c` will compile and assemble, but not link the code.
* The option `-N` will link the program code *without* the default standard C libraries, `stdlib` and `stdio`.
* The option `-o` can be used to set the generated binary file program name.  The default name is the same as the C source file.
* The linker build number is used to set the binary program Elf/OS version number.
* The assembly list file and linker symbol map contain useful information for debugging.


Stack Frame
------------

When calling a function ElfC will push the function arguments from right to left onto the stack. ElfC then sets the register RB to current value of R7, the expression stack pointer, to define the base of the stack frame.  Character arguments are promoted to integers when passed as arguments, and pointers are passed as integer values. This means that the stack size of every argument is 2 bytes.

Inside the function, local (auto) variables are allocated on the stack.  The stack size for integers and pointers is two bytes.  Characters occupy one byte of the two byte stack slot. Arrays, structures and unions are expanded to an even number of bytes when allocated on the stack.

If the first local (auto) variable in a function is a structure or union, then an integer-sized padding element is added first, to allow the structure or union to exist on the structure in case it becomes the return value of the function.

*Example 1:*
```
int fn1(int n, char c, int *p) {
   int  i1;
   char c1;
   char a[3];
   ...
   return i1;
}

```

*Stackframe 1:*
<table>
<tr><th>Stack Offset</th><th>object</th><th>Stack Size</th><th>Description</th><tr>
<tr><td>+4</td><td>p</td><td>2</td><td>pointer</td></tr>
<tr><td>+2</td><td>c</td><td>2</td><td>char promoted to int</td></tr>
<tr><td>0</td><td>n</td><td>2</td><td>integer</td></tr>
<tr><th colspan="4">RB points to the Base of the Stack Frame</th></tr>
<tr><td rowspan="2">-2</td><td rowspan="2">i1</td><td rowspan="2">2</td><td>integer (MSB)</td></tr>
<tr><td>integer (LSB)</td></tr>
<tr><td rowspan="2">-4</td><td>xx</td><td rowspan="2">2</td><td >padding byte</td></tr>
<tr><td>c1</td><td>character</td></tr
<tr><td rowspan="4">-4</td><td>xx</td><td rowspan="4">4</td><td>padding byte</td></tr>
<tr><td>a[2]</td><td rowspan="3">array characters</td></tr>
<tr><td>a[1]</td></tr>
<tr><td>a[0]</td></tr>
<tr><th colspan="4">R7 points to the Bottom of Expression Stack</th></tr>
</table>

*Example 2:*
```
struct scrabble_tile {
  char letter;
  int  score;
};

/* get the tile from a player's rack */
struct scrabble_tile rack(int pos) {
    struct scrabble_tile tile;
    /* get the scrabble tile from rack, draw new tile if needed */
    ...

    /* return tile at position in rack */
    return tile;
}

```

*Stackframe for Example 2*
<table>
<tr><th>Stack Offset</th><th>object</th><th>Stack Size</th><th>Description</th><tr>
<tr><td>0</td><td>pos</td><td>2</td><td>integer</td><tr>
<tr><th colspan="4">RB points to the Base of Stack Frame</th></tr>
<tr><td>-2</td><td>_pad</td><td>2</td><td>2 byte padding for possible structure return</td><tr>
<tr><td rowspan="4">-6</td><td rowspan="2">scrabble_tile.score</td><td rowspan="4">4</td><td>int (MSB)</td></tr>
<tr><td>int (LSB)</td></tr>
<tr><td>xx</td><td>padding byte</td></tr>
<tr><td>scrabble_tile.letter</td><td>char</td></tr>
<tr><th colspan="4">R7 points to the Bottom of Expression Stack</th></tr>
</table>

*Notes:*
* The default stack size is 2 bytes, the integer size.
* Arguments are pushed on the stack from right to left, so that the first argument is at offset 0.
* After the arguments are pushed to the expression stack, RB is set to the value of R7.
* The base pointer RB defines the base address of the stack frame.
* Local variables are the allocated onto the expression stack.
* Arguments are referenced by positive offsets from the base address.
* Local variables are referenced by negative offsets from the base address.
* RB is used as a reference to access a function's arguments and local variables on the stack frame.
* Since they are stack pointers, R7 and RB point to the address one *below* the data on the stack.
* Character arguments are promoted to int on the expression stack.
* Arrays are padded to an even byte size on the expression stack.
* Structures and unions have their fields padded to the stack size.
* If a structure/union is the first local (auto) variable in the function, an integer-sized padding element is added so that the structure may be used for a return value.
* At the end of a function, R7 is moved back by the size of the local variables, and the value of R7 is checked with RB to validate that the expression stack has returned to its base address.
* If R7 does not equal RB when checked, then a *Stack Creep Error* is issued, and the program terminates.
* Otherwise the function returns, and the program continues.


Registers Used
---------------

<table>
<tr><th>Input Files</th><th>Description</th><th>Output Files</th><th>Description</th></tr>
<tr><td>R0</td><td>DMA Pointer</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R1</td><td>Interrupt Handler</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R2</td><td>System Stack Pointer (SP)</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R3</td><td>Program Instruction and Subroutine Argument Pointer</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R4</td><td>SCRT Call Routine</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R5</td><td>SCRT Return Routine</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R6</td><td>SCRT Argument and Return Point</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R7</td><td>Expression Stack Pointer (ESP)</td><td>ElfC</td><td>Reserved</td></tr>
<tr><td>R8</td><td>Expression Temp Value</td><td>ElfC</td><td>General Use</td></tr>
<tr><td>R9</td><td>Subroutine Pointer</td><td>ElfC</td><td>Reserved</td></tr>
<tr><td>RA</td><td>Accumulator and Return Value</td><td>ElfC</td><td>Reserved</td></tr>
<tr><td>RB</td><td>Caller Stack Frame Base Pointer</td><td>ElfC</td><td>Reserved</td></tr>
<tr><td>RC</td><td>Counter</td><td>User</td><td>General Use</td></tr>
<tr><td>RD</td><td>Destination Pointer or Data Value</td><td>User</td><td>General Use</td></tr>
<tr><td>RE.1</td><td>Baud Rate Byte</td><td>OS</td><td>Reserved</td></tr>
<tr><td>RE.0</td><td>SCRT Scratch Byte</td><td>OS</td><td>General Use</td></tr>
<tr><td>RF</td><td>Buffer Pointer</td><td>User</td><td>General Use</td></tr>
</table>

*Notes:*
* *SCRT stands for the "Standard Call and Return" routine.*
* *'Reserved' means that the values of these registers should not be changed, even when not in use by its owner.*
* *'General Use' means that the register value may be changed when not directly in use by its owner.*


Code Generation Interface
--------------------------
The following subroutines are invoked by the ElfC code generation code in the `cgelf.c` source file.

<table>
<tr><th colspan="2">Arithmetic Subroutines</th></tr>
<tr><th>Name</th><th>Description</th></tr>
<tr><td>add16</td><td>Add 2 signed 16-bit numbers on expression stack</td></tr>
<tr><td>div16</td><td>Divide 2 signed 16-bit numbers on expression stack</td></tr>
<tr><td>mdsgn16</td><td>Prepare 2 signed numbers on expression stack for Multiplication or Division</td></tr>
<tr><td>mod16</td><td>Compute the Modulo of 2 numbers on expression stack</td></tr>
<tr><td>mul16</td><td>Multiply 2 signed 16-bit numbers on expression stack</td></tr>
<tr><td>neg16</td><td>Negate 16-bit integer on expression stack</td></tr>
<tr><td>shl16</td><td>Left Shift 16-bit integer on expression stack one bit</td></tr>
<tr><td>shr16</td><td>Right Shift 16-bit integer on expression stack one bit</td></tr>
<tr><td>sub16</td><td>Subtract 2 signed 16-bit numbers on expression stack</td></tr>
</table>

<table>
<tr><th colspan="2">Boolean and Comparison Subroutines</th></tr>
<tr><th>Name</th><th>Description</th></tr>
<tr><td>and16</td><td>And two 16-bit numbers on expression stack</td></tr>
<tr><td>bool16</td><td>Convert 16-bit value on expression stack to its boolean value (1 or 0)</td></tr>
<tr><td>eq16</td><td>Compare 2 16-bit values for equality</td></tr>
<tr><td>false16</td><td>Push boolean false value (0) onto expression stack</td></tr>
<tr><td>gt16</td><td>Compare 2 signed 16-bit values for SOS greater than TOS</td></tr>
<tr><td>gte16</td><td>Compare 2 signed 16-bit values for SOS greater or equal TOS</td></tr>
<tr><td>inv16</td><td>Invert a 16-bit integer on expression stack</td></tr>
<tr><td>lt16</td><td>Compare 2 signed 16-bit values for SOS less than TOS</td></tr>
<tr><td>lte16</td><td>Compare 2 signed 16-bit values for SOS less or equal TOS</td></tr>
<tr><td>ne16</td><td>Compare 2 16-bit values for non-equality</td></tr>
<tr><td>not16</td><td>Boolean Not value of a 16-bit number on the expression stack</td></tr>
<tr><td>or16</td><td>Or two 16-bit numbers on expression stack</td></tr>
<tr><td>true16</td><td>Push boolean true value (1) onto expression stack</td></tr>
<tr><td>uge16</td><td>Compare 2 unsigned 16-bit values for SOS greater or equal TOS</td></tr>
<tr><td>ugt16</td><td>Compare 2 unsigned 16-bit values for SOS greater than TOS</td></tr>
<tr><td>ule16</td><td>Compare 2 unsigned 16-bit values for SOS less or equal TOS</td></tr>
<tr><td>ult16</td><td>Compare 2 unsigned 16-bit values for SOS less than TOS</td></tr>
<tr><td>xor16</td><td>Exclusive Or (xor) two 16-bit numbers on expression stack</td></tr>
</table>

<table>
<tr><th colspan="2">Stack Manipulation Subroutines</th></tr>
<tr><th>Name</th><th>Description</th></tr>
<tr><td>deref16</td><td>Replace a pointer on the expression stack with the 16-bit value it references</td></tr>
<tr><td>deref8</td><td>Replace a pointer on the expression stack with the 8-bit value it references</td></tr>
<tr><td>dget16</td><td>Get a 2-byte value from the expression stack (ESP is unchanged)</td></tr>
<tr><td>dpop16</td><td>Pop a 2-byte value from the expression stack</td></tr>
<tr><td>dpush16</td><td>Pop a 2-byte value from the expression stack</td></tr>
<tr><td>epush16</td><td>Push a 2-byte constant onto expression stack</td></tr>
<tr><td>epush8</td><td>Push 1-byte char value onto expression stack</td></tr>
<tr><td>esmove</td><td>Move the expression stack pointer by a signed offset</td></tr>
<tr><td>mcopy</td><td>Copy the contents of a structure or union referenced by the pointer at the SOS into the structure or union referenced by the pointer at the TOS</td></tr>
<tr><td>sclsos2n</td><td>Scale a 16-bit pointer offset at the SOS of the expression stack by a power of 2</td></tr>
<tr><td>scltos2n</td><td>Scale a 16-bit pointer offset at the TOS of the expression stack by a power of 2</td></tr>
<tr><td>stkchk</td><td>Check the expression stack for a stack creep error and return DF = 1 if the stack pointer has not returned to the base pointer.</td></tr>
<tr><td>swap16</td><td>Swap the two 16-bit numbers at TOS and SOS on expression stack </td></tr>
<tr><td>unscl2n</td><td>Unscale a 16-bit pointer difference at the TOS of the expression stack by a power of 2</td></tr>
</table>

<table>
<tr><th colspan="2">Local Variable Subroutines</th></tr>
<tr><th>Name</th><th>Description</th></tr>
<tr><td>laddr16</td><td>Put the address of a local variable onto the expression stack</td></tr>
<tr><td>ldec16</td><td>Decrement a 16-bit local variable value</td></tr>
<tr><td>ldec8</td><td>Decrement an 8-bit local variable value</td></tr>
<tr><td>lget16</td><td>Get a 2-byte local variable (ESP is unchanged)</td></tr>
<tr><td>linc16</td><td>Increment a 16-bit local variable value</td></tr>
<tr><td>linc8</td><td>Increment an 8-bit local variable value</td></tr>
<tr><td>linit16</td><td>Initialize a local variable to a 16-bit (ESP is unchanged) </td></tr>
<tr><td>lpdec16</td><td>Decrement a local pointer variable by size bytes</td></tr>
<tr><td>lpinc16</td><td>Increment a local pointer variable by size bytes</td></tr>
<tr><td>lpush16</td><td>Push a 16-bit local variable value onto the expression stack</td></tr>
<tr><td>lpush8</td><td>Push an 8-bit local variable value onto the expression stack</td></tr>
<tr><td>lset16</td><td>Set a 2-byte local variable with value in the RA register (ESP is unchanged)</td></tr>
<tr><td>lstor16</td><td>Copy a 2-byte value from the expression stack into a local variable (ESP is unchanged)</td></tr>
<tr><td>lstor8</td><td>Copy a 1-byte value from the expression stack into a local variable (ESP is unchanged)</td></tr>
</table>

<table>
<tr><th colspan="2">Pointer Reference Subroutines</th></tr>
<tr><th>Name</th><th>Description</th></tr>
<tr><td>pdec16</td><td>Decrement a 2-byte value referenced by the pointer value in the RA register (ESP is unchanged)</td></tr>
<tr><td>pdec8</td><td>Decrement a 1-byte value referenced by the pointer value in the RA register (ESP is unchanged)</td></tr>
<tr><td>pdecptr</td><td>Decrement a pointer value referenced by the pointer value in the RA register (ESP is unchanged)</td></tr>
<tr><td>pinc16</td><td>Increment a 2-byte value referenced by the pointer value in the RA register (ESP is unchanged)</td></tr>
<tr><td>pinc8</td><td>Increment a 1-byte value referenced by the pointer value in the RA register (ESP is unchanged)</td></tr>
<tr><td>pincptr</td><td>Increment a pointer value referenced by the pointer value in the RA register (ESP is unchanged)</td></tr>
<tr><td>psave</td><td>Get a pointer value from the expression stack and store it in the RA register (ESP is unchanged)</td></tr>
<tr><td>pstor16</td><td>Get a 2-byte value from the expression stack and store it via a pointer value in RA (ESP is unchanged) </td></tr>
<tr><td>pstor8</td><td>Get a 1-byte value from the expression stack and store it via a pointer value in RA (ESP is unchanged)</td></tr>
</table>

<table>
<tr><th colspan="2">Global and Static Variable Subroutines</th></tr>
<tr><th>Name</th><th>Description</th></tr>
<tr><td>vdec16</td><td>Decrement 2-byte global or static variable</td></tr>
<tr><td>vdec8</td><td>Decrement 1-byte global or static variable</td></tr>
<tr><td>vinc16</td><td>Increment 2-byte global or static variable</td></tr>
<tr><td>vinc8</td><td>Increment 1-byte global or static variable</td></tr>
<tr><td>vpdec16</td><td>Decrement a global or static pointer to a variable value of size bytes</td></tr>
<tr><td>vpinc16</td><td>Increment a global or static pointer to a variable value of size bytes</td></tr>
<tr><td>vpop16</td><td>Pop 2-byte global or static variable from expression stack</td></tr>
<tr><td>vpush16</td><td>Push 2-byte global or static variable onto expression stack</td></tr>
<tr><td>vpush8</td><td>Push 1-byte global or static variable onto expression stack</td></tr>
<tr><td>vstor16</td><td>Get a 2-byte value from the expression stack and store it in a global or static variable (ESP is unchanged)</td></tr>
<tr><td>vstor8</td><td>Get a 1-byte value from the expression stack and store it in a global or static variable (ESP is unchanged)</td></tr>
</table>

*Notes:*
* TOS stands for Top Of Stack.
* SOS stands for Second On Stack.
* ESP stands for Expression Stack Pointer.
* Take care when using the Stack Manipulation routines to keep the stack 2-byte aligned.
* All the Pointer Reference Subroutines leave the ESP unchanged
* All other subroutines with names containing *get*, *init*, *set* or *stor* leave the ESP unchanged.
* Local subroutine names begin with the letter *l*.
* Pointer subroutine names begin with the letter *p*.
* Global and Static Variable subroutine names begin with the letter *v*.


ElfC File Descriptor
--------------------
<table>
<tr><th>Byte Index</th><th>Description</th><th>Size</th></tr>
<tr><td>0-3</td><td>Current Offset</td><td>4</td></tr>
<tr><td>4-5</td><td>DTA Pointer</td><td>2</td></tr>
<tr><td>6-7</td><td>EOF</td><td>2</td></tr>
<tr><td>8</td><td>Flags Byte</td><td>1</td></tr>
<tr><td>9-12</td><td>Directory Sector</td><td>4</td></tr>
<tr><td>13-14</td><td>Directory Offset</td><td>2</td></tr>
<tr><td>15-18</td><td>Current Sector</td><td>4</td></tr>
<tr><td>19</td><td>Drive Number (Elf/OS v5)</td><td>1</td></tr>
<tr><td>20</td><td>Drive FS Type (Elf/OS v5)</td><td>1</td></tr>
<tr><td>21</td><td>1 Byte Padding</td><td>1</td></tr>
<tr><td rowspan ="2">22-533</td><td rowspan ="2">DTA</td><td rowspan ="2">512</td></tr>
</table>

*Notes:*
* *The total Size of ElfC File Descriptor is 534 bytes.*
* *The DTA begins 22 bytes offset from the start of the FD.*
* *This FD format is valid for Mini/DOS and Elf/OS v5*

Translation Limits
-------------------

The ANSI C89/C90 specification defines the following minimum translation limits in section 5.2.4.1 of the specification.  ElfC defines constants for most of these values that can be changed in the *defs.h* header file in the source code.

<table>
<tr><th>Description</th><th>ElfC Limit</th><th>Meets Spec?</th><th>Limiting Factor</th></tr>
<tr><td>15 nesting levels of compound statements</td><td>16</td><td>Yes</td><td>MAXBREAK</td></tr>
<tr><td>8 nesting levels of conditional inclusion</td><td>16</td><td>Yes</td><td>MAXIFDEF</td></tr>
<tr><td>12 pointer, array, and function declarators (in any combination) in a declaration</td><td>15</td><td>Yes, with Exceptions</td><td>MAXPTR (See Notes Below for Exceptions)</td></tr>
<tr><td>31 nesting levels of parenthesized declarators</td><td>1</td><td>No</td><td>Parentheses in a declaration are only supported when declaring a function pointer.</td></tr>
<tr><td>32 nesting levels of parenthesized expressions within a full expression</td><td>1024</td><td>Yes</td><td>NSYMBOLS</td></tr>
<tr><td>31 significant initial characters in an internal identifier or a macro name</td><td>16</td><td>No</td><td>NAMELEN</td></tr>
<tr><td>6 significant initial characters in an external identifier</td><td>16</td><td>Yes</td><td>NAMELEN</td></tr>
<tr><td>511 external identifiers in one translation unit</td><td>1024</td><td>Yes</td><td>NSYMBOLS</td><tr>
<tr><td>127 identifiers with block scope declared in one block</td><td>1024</td><td>Yes</td><td>NSYMBOLS</td><tr>
<tr><td>1024 macro identifiers defined in one translation unit</td><td>1024</td><td>Yes</td><td>NSYMBOLS</td><tr>
<tr><td>31 parameters in one function definition</td><td>16</td><td>No</td><td>MAXFNARGS</td></tr>
<tr><td>31 arguments in one function call</td><td>16</td><td>No</td><td>MAXFNARGS</td></tr>
<tr><td>31 parameters in one macro definition</td><td>8</td><td>No</td><td>MAXMARGS</td></tr>
<tr><td>31 arguments in one macro invocation</td><td>8</td><td>No</td><td>MAXMARGS</td></tr>
<tr><td>509 characters in a logical source line</td><td>512</td><td>Yes</td><td>TEXTLEN</td></tr>
<tr><td>509 characters in a character string literal (after concatenation)</td><td>512</td><td>Yes</td><td>TEXTLEN</td></tr>
<tr><td>32767 bytes in an object (in a hosted environment)</td><td>65535</td><td>Yes</td><td>Asm/02 and Link/02 Limit</td></tr>
<tr><td>8 nesting levels for #included files</td><td>32</td><td>Yes</td><td>MAXFILES</td></tr>
<tr><td>257 case labels for a switch statement (including label for default case)</td><td>257</td><td>Yes</td><td>MAXCASE + 1 for default case label</td></tr>
<tr><td>127 members in a single structure or union</td><td>1024</td><td>Yes</td><td>NSYMBOLS</td></tr>
<tr><td>127 enumeration constants in a single enumeration</td><td>1024</td><td>Yes</td><td>NSYMBOLS</td></tr>
<tr><td>15 levels of nested structure or union definitions in a single declaration list</td><td>Not Supported</td><td>No</td><td>Structure declarations cannot be nested</td></tr>
</table>

*Notes:*
* Up to 15 levels of indirection is supported in a declaration involving pointers, arrays and structure/unions.
* ElfC does not support multi-dimensional arrays, e.g. `int a[3][4];` is not supported.
* Pointers to function pointers are not supported., e.g. `int (**f)();` is not supported.
* ElfC does not support pointers to pointers to structure or union pointers, e.g. `struct stc ***p;` is not supported.
* Only the supported parenthesized declaration syntax is `int (*f)()` which declares *f* as a function pointer.
* Maximum total number of symbols in the ElfC symbol pool is 16348 (POOLSIZE)
* Each of the various types of symbols in the symbol pool have a limit of 1024 (NSYMBOLS) for symbols of that type.
* Both Asm/02 and Link/02 generate and link object files in a 16-bit address space, giving a maximum limit of 64K.
* ElfC does not support nested structure/union declarations.
