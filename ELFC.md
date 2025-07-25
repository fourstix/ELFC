# ElfC Detailed Information

Types Supported
---------------

<table>
<tr><th><keyword></th><th>name</th><th>description</th><th>minimum</th><th>maximum</th></tr>
<tr><td>char</td><td>Character</td><td>8-bit unsigned</td><td>0</td><td>255</td></tr>
<tr><td>int</td><td>Integer</td><td>16-bit signed</td><td>-32767</td><td>32767</td></tr>
<tr><td>void</td><td>Void</td><td>No Value</td><td>0</td><td>0</td></tr>
<tr><td>int *</td><td rowspan="3">Pointer</td><td rowspan="3">16-bit unsigned</td><td rowspan="3">0</td><td rowspan="3">65535</td></tr>
<tr><td>char *</td></tr>
<tr><td>void *</td></tr>
<tr><td>int **</td><td rowspan="3">Pointer to a Pointer</td><td rowspan="3">16-bit unsigned</td><td rowspan="3">0</td><td rowspan="3">65535</td></tr>
<tr><td>char **</td></tr>
<tr><td>void **</td></tr>
<tr><td>int(*)()</td><td>Pointer to a Function</td><td>16-bit unsigned</td><td>0</td><td>65535</td></tr>
</table>

*Notes:*
* *Single dimension arrays of the above types are supported, such as int[] char\*[], etc.*
* *Structures and unions composed of the above types are supported.*
* *Pointers to structures and pointers to unions are supported.*
* *Typedef is supported.*

Registers Used
---------------

<table>
<tr><th>Register</th><th>Purpose</th><th>Owner</th><th>Availability</th></tr>
<tr><td>R0</td><td>DMA Pointer</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R1</td><td>Interrupt Handler, STG Breakpoint</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R2</td><td>System Stack Pointer (SP)</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R3</td><td>Program Instruction Pointer</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R4</td><td>SCRT Call Routine</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R5</td><td>SCRT Return Routine</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R6</td><td>SCRT Argument and Return Point</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R7</td><td>Expression Stack Pointer (ESP)</td><td>ElfC</td><td>Reserved</td></tr>
<tr><td>R8</td><td>Expression Temp Value</td><td>ElfC</td><td>General Use</td></tr>
<tr><td>R9</td><td>Expression Temp Value</td><td>ElfC</td><td>General Use</td></tr>
<tr><td>RA</td><td>Accumulator and Return Value</td><td>ElfC</td><td>Reserved</td></tr>
<tr><td>RB</td><td>Caller Stack Frame Base Pointer</td><td>ElfC</td><td>Reserved</td></tr>
<tr><td>RC</td><td>Counter</td><td>User</td><td>General Use</td></tr>
<tr><td>RD</td><td>Destination Pointer, Data Value</td><td>User</td><td>General Use</td></tr>
<tr><td>RE.1</td><td>Baud Rate Byte</td><td>OS</td><td>Reserved</td></tr>
<tr><td>RE.0</td><td>SCRT Scratch Byte</td><td>User</td><td>General Use</td></tr>
<tr><td>RF</td><td>Buffer Pointer</td><td>User</td><td>General Use</td></tr>
</table>

*Notes:*
* *SCRT stands for the "Standard Call and Return" routine.*
* *'Reserved' means that the values of these registers should not be changed, even when not in use by the OS or ElfC.*
* *'General Use' means that the register value may be changed when not directly in use by the OS or ElfC*

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
* *This FD format is valid for Mini-DOS and Elf/OS v5*

Additional Statements
---------------------

The following statement and preprocessor directive were added to SubC by ElfC to support inline Asm/02 code.

* The `asm` statement passes a string literal directly into the generated assembly file.

* The `#pragma` preprocessor directive can be used to directly insert a line of assembly code into the generated assembly file.


Print Conversions
------------------
* The flags `-, +, space, 0 and #` are supported.
* The width specification is suppored.
* The suppression operator `(\*)` is supported.
* The decimal precision is not supported.
* The length modifiers h, l (el) and L are not supported. 
* The `%d, %i, %o, %x, %X, %c, %s, %p, %n and %%` conversions are supported.
* The %u, %f, %e, %E, %g and %G conversions are not supported.

Scan Conversions
-----------------
* The width specification is suppored.
* The suppression operator `(\*)` is supported.
* The `%d, %i, %o, %x, %c, %s, %p, %n and %%` conversions are supported.
* The charset operators %[...] and %[^...] are supported.
* The %u, %f, %e, and %g conversions are not supported.

Unsupported Stdlib Functions
----------------------------

The following functions were omitted from the ElfC stdlib C library.

* double atof(char\* s);
* long atol(char\* s);
* double strtod(char\* s, char\*\* endp);
* long strtol(char\* s, char\*\* endp, int base
* unsigned long strtoul(char\* s, char\*\* endp, int base);
* long labs(long n);
* ldiv_t ldiv(long num, long denom);
* int system(char *s);
* char\* getenv(char *name);

*Notes:*
* *All the long and double utility functions were omitted because these types are not supported in the current version.* 
* *The system and genenv() have no equivalent functions in Elf/OS or MiniDOS* 


Unsupported Stdio Functions
----------------------------

The following functions were omitted from the ElfC stdio C library.

* FILE\* reopen(char\* filename, char \*mode, FILE\* stream);
* int setvbuf(FILE\* stream, char \*buf, int mode, int size);
* int setbuf(FILE\* stream, char \*buf;

*Note: Elf/OS and MiniDOS use their own buffering, and do not allow streams to be reassigned.*

Stdlib Modified Functions
-------------------------
* `lseek` takes two int arguments for the offset since long is not supported.
*  `div` uses a pointer to a div_t structure for the result, because returning a structure is not supported.
* `min` and `max` are implemented as functions because macro parameters are not supported.
* `itox` and `itou` are available to convert int values to hexadecimal and unsigned integer ASCII strings.

Stdio Modified Functions
-------------------------
* `ftell` and `fseek` use an int type value for position, since long type is not supported.
* `fflush` is implemented as a NOP.
* `tmpnam` creates a filename with form similar to `temp.00`.
* `fclose` will delete a temporary file created by `tmpfile` after closing it.
* Terminating a program by `abort` or without calling `fclose` to close a temporary file, may leave behind files created by `tmpfile`.

String Modified Functions
-------------------------
* `strlcpy` will copy up to a specified number (length - 1) of characters and then append a null.
* `strdup` will allocate memory for the size a string, copy the string into memory and then return a pointer to the duplicate string.

Stdarg Modified Functions
-------------------------
* The stdarg library is implemented by variable argument functions, because preprocessor macros do not support parameters.
* `va_arg` function does not include an argument for the type name, because macro parameters is not supported.
* `va_end` is implemented as a NOP.

Assert Modified Function
------------------------
* `assert` is implemented by function, because the preprocessor does not support macros with parameters.
* The `assert` function has arguments for the assertion, file name and line number. 
* If the macro `NDEBUG` is defined the `assert` function returns immediately.
* The `__FILE__` and `__LINE__` macros can be used as the file and line arguments, so the correct values are printed if the assertion is false.

Pre-Defined Macros
-------------------
* If `\_ELFCLIB\_` is defined, C code is compiled for an Elf/OS library procedure.
* If `\_STGROM\_`  is defined, assembly code for the STG ROM is created.
* `BRKPT` inserts assembly code to invoke the STG break point handler, when `\_STGROM\_` is defined.
* `__LINE__` inserts the current line number in the code file.
* `__FILE__` insert the current file name in the code file.
* If `NDEBUG` is defined, the `assert` function returns immediately, and the code for the assert message is suppressed.

*Note: `__LINE__` and `__FILE__` begin and end with **two** underscores.*

Unsupported Libraries
---------------------
* The `setjmp` library is not supported.
* The `signal` library is not supported.
* The `math` library is not supported, because there are no real types (float or double) in this release.
* The `time` library is planned for a future release.

Header files
------------
* The `float.h` header file is not supported.
* The `locale.h` header file is not supported.
* The `stdlib.h` header file implements definitions for `unistd.h`, `stddef.h` and `fcntl.h`.
* The `unistd.h`, `stddef.h` and `fcntl.h` header files are empty except for an `#include <stdlib.h>` statement.
