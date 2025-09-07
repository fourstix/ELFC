# ElfC Detailed Information

Types Supported
---------------

<table>
<tr><th>Keyword</th><th>Name</th><th>Description</th><th>Minimum</th><th>Maximum</th></tr>
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
* *Function pointers are limited to one single type, `int(\*)()`, and they have no argument types.*
* *Structures and unions composed of the above types are supported.*
* *Pointers to structures and pointers to unions are supported.*
* *Typedef is supported.*

Registers Used
---------------

<table>
<tr><th>Register</th><th>Purpose</th><th>Owner</th><th>Availability</th></tr>
<tr><td>R0</td><td>DMA Pointer</td><td>OS</td><td>Reserved</td></tr>
<tr><td>R1</td><td>Interrupt Handler</td><td>OS</td><td>Reserved</td></tr>
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
<tr><td>RE.0</td><td>SCRT Scratch Byte</td><td>OS</td><td>General Use</td></tr>
<tr><td>RF</td><td>Buffer Pointer</td><td>User</td><td>General Use</td></tr>
</table>

*Notes:*
* *SCRT stands for the "Standard Call and Return" routine.*
* *'Reserved' means that the values of these registers should not be changed, even when not in use by its owner.*
* *'General Use' means that the register value may be changed when not directly in use by its owner.*

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

Additional Statements
---------------------

The following statement and preprocessor directive were added to SubC by ElfC to support inline Asm/02 code.

* The `asm` statement passes a string literal directly into the generated assembly file.

* The `#pragma` preprocessor directive can be used to directly insert a line of assembly code into the generated assembly file.


Library Compiler Option 
------------------------

* The new `-L` ElfC option will compile and assemble a C source file into a prg file defining an Elf/OS (Mini/DOS) library procedure.

* The source file should contain a public function with same name as the file name of the C file. If no public function in the file matches the file name, an error will be generated.

* The procedure name will be the file name with the C prefix and serve as the public entry point for the procedure function.

* If needed, the compiler will emit an immediate jump to the public entry point function with the same name as the procedure.

* The entry point function's public name will be suppressed to prevent duplication of the procedure name when assembling.

* The prg produced by the assembler can then be incorporated into a library for Elf/OS or Mini/DOS.

* The file can contain public functions and public labels. These will be available in the procedure, along with the procedure function name.

* An Elf/OS (Mini/DOS) library is created by concatenating multiple procedure prg files.

Example:

The C file `abs.c` containing the function:
```
int abs(int n) {
  return (n < 0) ? -n : n;
  }
```
When compiled with:
```
..\elfc -L abs.c
```
Will produce the file abs.prg that can be concatenated into an Elf/OS (Mini/DOS) library, such as stdlib.lib. The library can then be linked to a C program to provide the `abs` function.  
```
type abort.prg abs.prg exit.prg > stdlib.lib 
```


Print Conversions
------------------
* The flags `-, +, space, 0 and #` are supported.
* The width specification is suppored.
* The suppression operator `*` is supported.
* The decimal precision is not supported.
* The length modifiers h, l (el) and L are not supported. 
* The `%d, %i, %o, %x, %X, %c, %s, %p, %n and %%` conversions are supported.
* The %u, %f, %e, %E, %g and %G conversions are not supported.

Scan Conversions
-----------------
* The width specification is suppored.
* The suppression operator `*` is supported.
* The `%d, %i, %o, %x, %c, %s, %p, %n and %%` conversions are supported.
* The charset operators `%[...]` and `%[^...]` are supported.
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
* *The system and genenv() have no equivalent functions in Elf/OS or Mini/DOS* 


Unsupported Stdio Functions
----------------------------

The following functions were omitted from the ElfC stdio C library.

* FILE\* reopen(char\* filename, char \*mode, FILE\* stream);
* int setvbuf(FILE\* stream, char \*buf, int mode, int size);
* int setbuf(FILE\* stream, char \*buf);

*Note: Elf/OS and Mini/DOS use their own buffering, and do not allow streams to be reassigned.*

Stdlib Modified Functions
-------------------------
*  Because long types are not supported, `lseek` takes two int arguments for the offset, and returns an int value, 0  for success or -1 for error.
*  `div` uses a pointer to a div_t structure for the result, because returning a structure is not supported.
* `min` and `max` are implemented as functions because macro parameters are not supported.
* `itox` and `itou` are available to convert int values to hexadecimal and unsigned integer ASCII strings.

Stdio Modified Functions
-------------------------
* `ftell` and `fseek` use an int type value for position, since long type is not supported.
* `fflush` is implemented as a NOP (No Operation) function.
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
* `va_end` is implemented as a NOP (No Operation) function.

Assert Modified Function
------------------------
* `assert` is implemented by function, because the preprocessor does not support macros with parameters.
* The `assert` function has arguments for the assertion, file name and line number. 
* If the macro `NDEBUG` is defined the `assert` function returns immediately.
* The `__FILE__` and `__LINE__` macros can be used as the file and line arguments, so the correct values are printed if the assertion is false.

Time Library
---------------------------


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

*Notes:*
* Many of the functions in C time library use static objects that may be over-written by other calls.

Unsupported Time Functions
---------------------------
The following functions were omitted from the ElfC time C library because Elf/OS v5 and Mini/DOS do not provide API for a clock or system time variable.  Equivalent functions that provide the same information through a time structure are provided instead.

* clock_t clock(void)
* time_t void(void)
* double difftime(time_t time2, time_t time1)
* time_t mktime(struct tm *tp)

Local Timezone information
---------------------------
ElfC does not support the _locale.h_ header, so the following function should be used to set time zone information and daylight savings time information before calling other time functions.

* void timezone(char \*tzname, int tzoff_min, int tzdst) 

*Notes:*
* _tzname_ is a string abbreviation for the time zone name, such as "EST" for US Eastern Standard Time.
* _tzoff_min_ is the offset from Universal Co-ordinated Time in minutes.  Offset values WEST of UTC should be negative, while offsets to the EAST are positive.
* _tzdst_ indicates if daylight savings time is in effect. It should be 1 if daylingt savings time is in effect, and 0 if not.


Equivalent Time Functions
--------------------------
The following functions provide equivalent time functions by through a pointer to a time structure rather than through a time_t system time variable.

* int  systime(struct tm \*tp) _(equivalent to the localtime() function)_
* int  utctime(struct tm \*tp) _(equivalent to the gmttime() function_)
* char \*cstime(struct tm \*tp) _(equivalent to the ctime() function_)

*Notes:*
* The _systime()_ function will populate the time structure pointed to by the tp argument with values from the OS kernel API.
* The _systime()_ function will use the time zone to set the _tm_isdst_ field, or will set _tm_isdst_ field to -1 (Unknown) if _timezone()_ function has not been called previously.
* The _\_dow()_ and _\_doy()_ internal time functions are used to set the tm_wday and tm_yday fields.
* The _utctime()_ function uses information set by the _timezone()_ to calculate Universal Co-ordinated Time (UTC).
* The _utctime()_ function may not be accurate if _timezone()_ has not be called previously.
* The _systime()_ and _utctime()_ return 1 if a Real Time Clock (RTC) was used to provide the current time and 0 if data values in the kernel were used instead.
* The _cstime()_ function will return a pointer to a buffer with a string representing the current time.
* The _cstime()_ function is equivalent to calling _systime()_ and passing the pointer with the result to _asctime()_. 

Internal Time Functions
-----------------------
The following internal time functions calculate the day of the week and day of the year from the fields of the time structure, and then sets the corresponding value in the time structure.

* void _dow(struct tm \*tp)
* void _doy(struct tm \*tp)

Supported Time Functions
-------------------------
The following functions are supported as documented.

* char \*asctime(struct tm *tp)
* int  strftime(char \*s, int smax, char \*fmt, struct tm \*tp);

*Notes:*

* _asctime()_ provides a pointer to a buffer with a simple string representation of the time.
* _strftim()_ formats the date and time information pointed to by _tp_ into a buffer _s_ using a format string _fmt_ that is similar to a printf format string.  
* _strftime()_ will write up to _smax_ characters are written into the buffer _s_ and will return the actual number of characters written, excluding '\0'.
* All of the ANSI (C89) strftime conversion formats are supported.

Strftime Conversions
---------------------
<table>
<tr><td>%a</td><td>abbreviated weekday name</td></tr>
<tr><td>%A</td><td>full weekday name</td></tr>
<tr><td>%b</td><td>abbreviated month name</td></tr>
<tr><td>%B</td><td>full month name</td></tr>
<tr><td>%c</td><td>local date and time representation</td></tr>
<tr><td>%d</td><td>day of month, as two digits with zero (01 to 31)</td></tr>
<tr><td>%H</td><td>hour (24-hour clock) as two digits with zero (00 to 23)</td></tr>
<tr><td>%I</td><td>hour (12-hour clock) as two digits with zero (01 to 12)</td></tr>
<tr><td>%j</td><td>day of year (001-366)</td></tr>
<tr><td>%m</td><td>month (01 to 12)</td></tr>
<tr><td>%M</td><td>minute (00 to 59)</td></tr>
<tr><td>%p</td><td>AM or PM</td></tr>
<tr><td>%S</td><td>second (00 to 60)</td></tr>
<tr><td>%U</td><td>week number of the year, Sunday as first day of week (00 to 53)</td></tr>
<tr><td>%w</td><td>weekday (0 to 6, Sunday is 0)</td></tr>
<tr><td>%W</td><td>week number of the year, Monday as first day of week (00 to 53)</td></tr>
<tr><td>%x</td><td>local date representation</td></tr>
<tr><td>%X</td><td>local time representation</td></tr>
<tr><td>%y</td><td>year without century (00 to 99)</td></tr>
<tr><td>%Y</td><td>year with century</td></tr>
<tr><td>%Z</td><td>time zone offset in hours and minutes, as set by timezone function</td></tr>
<tr><td>%%</td><td>percent sign (%)</td></tr>
</table>


Pre-Defined Macros
-------------------
* If `_ELFCLIB_` is defined, C code is compiled for an Elf/OS library procedure.
* If `_STGROM_`  is defined, assembly code to support the STG ROM is created.
* `BRKPT` inserts assembly code in the code file to invoke the STG break point handler, when `_STGROM_` is defined.
* `__LINE__` inserts the current line number in the code file.
* `__FILE__` insert the current file name in the code file.
* If `NDEBUG` is defined, the `assert` function returns immediately, and the code for the assert message is suppressed.

*Note: The `__LINE__` and `__FILE__` macros begin and end with **two** underscores.*

Unsupported Libraries
---------------------
* The `setjmp` library is not supported.
* The `signal` library is not supported.
* The `math` library is not supported, because there are no real types (float or double) in this release.


Header files
------------
* The `float.h` header file is not supported.
* The `locale.h` header file is not supported.
* The `stdlib.h` header file implements definitions for `unistd.h`, `stddef.h` and `fcntl.h`.
* The `unistd.h`, `stddef.h` and `fcntl.h` header files are empty except for a single `#include <stdlib.h>` statement.
