math32# ElfC Detailed Information

Documentation
---------------
* [ELFC General Information](README.md)
* ELFC Detailed Information (This Page)
* [ELFC Internal Information](INSIDE.md)

Types Supported
---------------

<table>
<tr><th>Keyword</th><th>Name</th><th>Description</th><th>Minimum</th><th>Maximum</th></tr>
<tr><td>char</td><td rowspan="2">Character</td><td rowspan="2">8-bit unsigned</td><td rowspan="2">0</td><td rowspan="2">255</td></tr>
<tr><td>unsigned char</td></tr>
<tr><td>signed char</td><td>Signed Character</td><td>8-bit signed</td><td>-128</td><td>127</td></tr>
<tr><td>int</td><td rowspan="3">Signed Integer</td><td rowspan="3">16-bit signed</td><td rowspan="3">-32768</td><td rowspan="3">32767</td></tr>
<tr><td>signed int</td></tr>
<tr><td>signed</td></tr>
<tr><td>unsigned int</td><td rowspan="2">Unsigned Integer</td><td  rowspan="2">16-bit unsigned</td><td  rowspan="2">0</td><td  rowspan="2">65535</td></tr>
<tr><td>unsigned</td></tr>
<tr><td>void</td><td>Void</td><td>No Value</td><td>0</td><td>0</td></tr>
<tr><td>int *</td><td rowspan="5">Pointer to Integer</td><td rowspan="5">16-bit unsigned</td><td rowspan="5">0</td><td rowspan="5">65535</td></tr>
<tr><td>signed int *</td></tr>
<tr><td>signed *</td></tr>
<tr><td>unsigned int *</td></tr>
<tr><td>unsigned *</td></tr>
<tr><td>char *</td><td rowspan="3">Pointer to Character</td><td rowspan="3">16-bit unsigned</td><td rowspan="3">0</td><td rowspan="3">65535</td></tr>
<tr><td>unsigned char *</td></tr>
<tr><td>signed char *</td></tr>
<tr><td>void *</td><td>Pointer to Void</td><td>16-bit unsigned</td><td>0</td><td>65535</td></tr>
<tr><td>int **</td><td rowspan="5">Pointer to a Pointer to Integer</td><td rowspan="5">16-bit unsigned</td><td rowspan="5">0</td><td rowspan="5">65535</td></tr>
<tr><td>signed int **</td></tr>
<tr><td>signed **</td></tr>
<tr><td>unsigned int **</td></tr>
<tr><td>unsigned **</td></tr>
<tr><td>char **</td><td rowspan="3">Pointer to a Pointer to Character</td><td rowspan="3">16-bit unsigned</td><td rowspan="3">0</td><td rowspan="3">65535</td></tr>
<tr><td>unsigned char **</td></tr>
<tr><td>signed char **</td></tr>
<tr><td>void **</td><td>Pointer to a Pointer to Void</td><td>16-bit unsigned</td><td>0</td><td>65535</td></tr>
<tr><td>int(*)()</td><td>Pointer to a Function</td><td>16-bit unsigned</td><td>0</td><td>65535</td></tr>
</table>

*Notes:*
* *Arrays of the above types are supported, such as `int[][]`, `char\*[]`, etc.*
* *Function pointers are limited to one single type, `int(\*)()`, and they have no argument types.*
* *Structures and unions composed of the above types are supported.*
* *Pointers to structures and pointers to unions are supported.*
* *Typedef is supported.*

Type Conversions
-----------------
ElfC follows the C "usual arithmetic conversions" The C Programming Language, 2nd Edition describes these rules in Section 2.7, Type Conversions, on page 42, and in Appendix A, Section A6.5 Arithmetic Conversions, on page 198. Since long, float and double types are not supported, these can be simplified as the two rules below.

* Signed and unsigned character types are promoted to int.
* If either of the operands are unsigned int, then (signed) int operator is promoted to unsigned.

*Notes:*
* Since character types are 8-bit types that fit completely into a subset of the 16-bit int type, they will keep their signed or unsigned value when promoted.
* A negative signed character value promotes to the same negative int value, and an unsigned charater value promotes to the same positive int value.
* Since int types do *not* fit completely into the range of unsigned int types, a negative int value will promote to a large positive value.
* A positive signed int value promotes to the same positive unsigned int value.

*Examples:*
These examples are in the promote.c example program.
```c
#include <stdio.h>

unsigned char uc =  77;
signed char   sc = -7;

int main() {
  char c;
  c = uc + sc;

  printf("char c = '%c' (%d)\n", c,c);
}
```
This program will print:
```
char c = 'F' (70)
```
The value uc promotes to int 77 and sc promotes to int -7, and 77 + (-7) = int 70, which is then assigned
back to unsigned char c as 'F' or 70.

```c
#include <stdio.h>

unsigned int  ui1 =  7;
signed int    i   = -77;

int main() {
  unsigned int ui2, ui3;

  ui2 = ui1 + i;
  printf("unsigned int ui2 = %u (%#x%)\n", ui2, ui2);
}
```
This program will print:
```
unsigned int ui2 = 65466 (0xffba)
```
In this example the int value -77 promotes to the unsigned int value of 65459, and 65459 plus the unigned int value 7 equals the unsigned int value of 65566.

Scope
------

ElfC supports declarations made in *global* scope and *local* scope.

If the declaration appears outside of any function then it is said to have *global* scope, which terminates at the end of the file.

If the declaration appears within a function definition or within the list of parameter declarations in a function definition, the identifier has *local* scope.

ElfC does not support declarations made in *block* scope.  Declarations cannot be declared within a block defined by a pair of braces, unless that block is the definition of a function.

If an identifier is declared by declaration with *local* scope, then it is only available within the function where it was declared.

If an identifier is declared by declaration with *global* scope, then it is available throughout the file where it was declared.

Storage Class Specifiers
--------------------------
ElfC supports the C standard type declaration syntax as specified in ANSI C C89/C90 specification. The declaration type may be prefixed by a storage class specifier, a type qualifier or both. If both are used, the storage class specifier must come before the type qualifier.

<table>
<tr><th>Storage Class Specifiers</th></tr>
<tr><td>extern</td></tr>
<tr><td>static</td></tr>
<tr><td>auto</td></tr>
<tr><td>register</td></tr>
<tr><td>typedef</td></tr>
</table>

*Notes:*
The `auto` and `register` storage class specifiers may only be used in local scope. ElfC will emit an error if they are used in global scope.

The `register` storage class specifier is treated the same as `auto`, except if the `const` type qualifier is used, then ElfC will emit an error because that combination is forbidden by the ANSI C C89/C90 specification.

The `auto` storage class specifier is the default for *local* scope declarations and `static` is the default for *global* scope declarations.

The `typedef` keyword is used to define user types.

Types Qualifiers
-----------------

<table>
<tr><th>Type Qualifiers</th></tr>
<tr><td>const</td></tr>
<tr><td>volatile</td></tr>
<tr><td>const volatile</td></tr>
<tr><td>volatile const</td></tr>
</table>

The type qualifier `volatile` is accepted, and will suppress optimization.

The type qualifier `const` is supported for variables and pointers to constant variables.

Either `volatile const` or `const volatile` are accepted as valid syntax, and are treated exactly the same.

If a storage class specifier is used in a declaration, the type qualifier must come after it.

Per the ANSI C C89/C90 specification, `register` variables cannot be made constant. ElfC accepts the `register` keyword in a local declaration, but ignores it unless the variable is also declared `const`, in that case ElfC will emit an error.

Functions may be declared to return a `const` value. Per the ANSI C C89/C90 specification, `const` is ignored since a function may never be an lvalue.

Arguments to a function may be declared as `const` and ElfC will treat these arguments as initialized inside the function.  An attempt to assign a value to a `const` argument inside the function is considered an error.

A pointer to an unqualified variable can be assigned to a pointer to a `const` or `volatile` variable, and vice versa.

Type qualifiers are ignored when considering if two types are compatible.

**Implementation Defined Behavior**

*Note:* This behavior is not specified by the ANSI C89/C90 specification, but may contradict behavior specified in C99 and later versions.

ElfC does not require immediate initialization in the declaration of a `const` variable, since ElfC does not fully support all the possible declaration type initializations.

ElfC allows variables to be declared as `const` and initialized later by an assignment in the code.  However, a second attempt at assignment will be treated as an error.

The `const` keyword is supported for static (and global) arrays, and `const` arrays must be initialized when declared.

User defined types may include `const` in their typedef definition, and `const` may be
applied to an existing user defined type.

The `const` keyword is ignored for structures and unions. ElfC will emit a warning message when `const` is ignored in these cases.

The `const` keyword is supported for members inside structures and unions.

ElfC does not prevent the assignment of a pointer to a `const` or `volatile` variable to an unqualified pointer.

Functions may be declared to return a `volatile` value and arguments may be qualified as `volatile` but ElfC will ignore the `volatile` keyword, per the ANSI C C89/C90 specification.

The `volatile` keyword is ignored for structures and unions. ElfC will emit a warning message when `volatile` is ignored in these cases.

The `volatile` keyword is supported for the members inside structures and unions.

User defined types may include `volatile` in their typedef definition, and `volatile` may be applied to an existing user defined type.

**Differences from ANSI C89/C90**

*Note:* The following behavior differs from the ANSI C89/C90 specification.

Neither `const` pointers to (varying) variables, nor `const` pointers to `const` variables are supported by ElfC, i.e. the syntaxes `int * const p;` and `const int * const p;` are *not* supported, and will emit an error.

The `const` keyword is *not* supported for local (auto) arrays, because ElfC does not support initializing local arrays.

Multi-dimensional Arrays
-------------------------

Mult-dimensional Arrays in C are arrays where the elements are other arrays.  The array data is stored in Row-Major form. _The C Programming Language, 2nd Edition_ describes arrays in _Chapter 5: Pointers and Arrays_.

If a multi-dimensional array is an incomplete array, only the first dimension is unspecified, eg. `int a[][3];` declares an incomplete array with two dimensions.

When an array reference is converted to an address reference, the process is called *pointer decay*. The word *decay* indicates that information about the array (the size of one of its dimensions) is lost when the array is converted to a pointer.

When pointer decay is applied, a multi-dimensional array is converted to a pointer to its first element.

When an array is used as the parameter to a function, it is passed by pointer decay as an array pointer.

ElfC supports array pointers internally, so a multi-dimensional array function parameter decays into a pointer to an array of one dimension less, eg. `int a[2][3]` decays into `int (*)a[3]`, a pointer to an array of three elements.

A one dimensional array decays into a pointer to its element type, eg. `int a[4]` decays into `int *`, a pointer to int.

ElfC will decay an array reference into a non-lvalue pointer that can be assigned to a pointer of the element base type, following the *Pointer Decay Rule* below.

**Pointer Decay Rule**

Pointer decay is formerly defined as:
```
Any lvalue expression of array type, when used in any context other than

* as the operand of the address-of operator
* as the operand of sizeof
* as the string literal used for array initialization

undergoes a conversion to the non-lvalue pointer to its first element. The result is not an lvalue.
```

**Example 1:**

int a[2][3] = {1,2,3,4,5,6};

<table>
<tr><th>Reference</th><th>Assignable Type</th><th>Value</th></tr>
<tr><td>a[0][0]</td><td>int</td><td>1</td></tr>
<tr><td>&a[0][0]</td><td rowspan="5">int * (via pointer decay)</td><td rowspan="5">Address of a[0][0]</td></tr>
<tr><td>a</td></tr>
<tr><td>&a</td></tr>
<tr><td>a[0]</td></tr>
<tr><td>&a[0]</td></tr>
<tr><td>a[1][0]</td><td>int</td><td>4</td></tr>
<tr><td>&a[1][0]</td><td rowspan="3">int * (via pointer decay)</td><td rowspan="3">Address of a[1][0]</td></tr>
<tr><td>a[1]</td></tr>
<tr><td>&a[1]</td></tr>

</table>

Notes:
* Multi-dimensional arrays are arrays of arrays.
* The array `a` is an array of two arrays of three integer elements, ie array[2] of array[3] of int.
* The references `a`, `&a`, `a[0]`, `&a[0]`, and `&a[0][0]` all yield the same value, the address of the first element (a[0][0]) of the array.
* The references `a[1]`, `&a[1]`, and `&a[1][0]` all yield the same value, the address of the first element of the second array of thee elements, ie. the first element of the array `a[1]` is `a[1][0]`.
* These array references are all assignable to the base type `int *` through pointer decay, although some cases will result in a pointer indirection level warning.
* ElfC follows the three exceptions noted in the above *Pointer Decay Rule* so that `&`, `sizeof` and a string literal used for array initialization all work as expected.

**Example 2:**

int a[2][3] = {1,2,3,4,5,6};

The array `a` may be passed to a function as a parameter by declaring the function one of three ways:

1. As a function declared with fully specified array parameter:
`int function1(int arr[2][3], int rows);`

2. As a function declared with an incompletely specified array parameter:
`int function2(int arr[][3], int rows);`

3. As a function declared with a pointer to the element base type:
`int function3(int *p, int rows, int cols)`

Each of these functions would be called with array `a` as a parameter, as follows:
1. `function1(a, 2);`
2. `function2(a, 2);`
2. `function3(a, 2, 3);`

Notes:
* The array parameters in function1 and function2 are the same, since the array parameter decays into a pointer to an array of three integers in both cases.
* The first index in the array parameter in function1 is ignored, which is why the rows value must be passed as a separate parameter, even though it was specified.
* A pointer to the element base type can be used instead, as in function3, but in that case one needs to pass the rows and columns values to do the pointer arithmetic manually.


**Implementation Defined Behavior**

* ElfC only supports array pointers internally and for passing arrays as function parameters.
* Array references, outside of function parameters, decay into a pointer assignable to a pointer to the base type, with the address value of the first element.

**Differences from ANSI C89/C90**

* Declaring a variable as a pointer to an array type is not supported., e.g. `int (*)a[];` is not supported.
* An array type may be declared in a `typedef` or in a variable declaration, but not both.

Initialization
---------------

* ElfC supports initialization of arrays and structures.
* Nested initializations are supported for structures containing arrays and other structures, and for arrays of structures.
* Uninitialzed values are set to zero.
* ElfC currently does not support additional nested braces in an initialization, unless it defines a member structure or array.

**Arrays may be initializd by lists of values**
```c
int a[2][3] = {1,2,3,4};
char vowels[5] = {'a','e','i','o','u'};
int values[] = {10, 20, 30};
```
*Note:*
* Unititialized values at the end of the list are set to 0.
* ElfC does not pad the inner dimensions of multi-dimensional arrays, so the first example is initialized as `{1,2,3,4,0,0}` and *not* `{1,2,0,3,4,0}`

**An array of characters may be initializd by a string**
```c
char word[6] = "first";
char greeting[] = "hello";
```
*Notes:*
* ElfC will not silently remove the NULL at the end of an initialization string, when the string is one character too long for an array.
* The size of the array must include the null at end of string.


**An array of character pointers may be initializd by a list of strings**
```c
char *prizes[3] = {"first", "second", "third"};
char *birds[] = {"crow", "hawk", "owl", "robin"};
```

**A structure may be initialized by a list of member values, including arrays and other structures, enclosed in braces**

```c
struct point {
  int x;
  int y;
  char *name;
};

struct line {
  struct point p1;
  struct point p2;
  char code[3];
};

struct point p1 = {1, 1, "one"};
struct point points[] = {{2, 20, "two"},  {30, 3, "three"}};
struct line line1 = {{5, 6, "a"},  {11, 12, "b"}, {'a','b'}}
```

Local Labels and `goto`
-----------------------

ElfC supports local labels and goto.

Local labels have functional scope and their own namespace.

The `goto` keyword can be used to jump directly to a local label within the same function.

There are few restrictions on local label locations and goto.  For example, they may jump into the body of an iteration statement, like `for` or `while` statement, bypassing any initializations or tests done at the beginning.

ElfC will emit a warning when a local label is defined within the body of an iteration statement, but the ANSI C89/C90 specification does not prohibit this. (Jumping into an iteration statement may bypass initializations, and is considered bad practice.)

Local labels and `goto` should be used with caution, if used at all.

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

The C file `cstime.c` containing the function:
```c
static struct tm _tm;

char *cstime(void) {
  systime(&_tm);
  return asctime(&_tm);
}
```
When compiled with:
```
..\elfc -L cstime.c
```
Will produce the file cstime.prg that can be concatenated into an Elf/OS (Mini/DOS) library, such as time.lib. The library can then be linked to a C program to provide the `cstime` function.
```
type systime.prg asctime.prg cstime.prg > time.lib
```

Stdio Print Conversions
-----------------------
* The flags `-, +, space, 0 and #` are supported.
* The width specification is supported.
* The suppression operator `*` is supported.
* The `%d, %i, %u, %o, %x, %X, %c, %s, %p, %n and %%` conversions are supported.
* The decimal precision is *not* supported.
* The length modifiers h, l (el) and L are *not* supported.
* The %f, %e, %E, %g and %G conversions are *not* supported.

Stdio Scan Conversions
----------------------
* The width specification is supported.
* The suppression operator `*` is supported.
* The `%d, %i, %u, %o, %x, %c, %s, %p, %n and %%` conversions are supported.
* The charset operators `%[...]` and `%[^...]` are supported.
* The %f, %e, and %g conversions are *not* supported.

When the `-M` option is specified, only the following conversions are supported. Using the
Elfio and Elfstd libraries, reduces the binary code size by about 2K bytes.

Elfio Print Conversions  (-M option)
------------------------------------
* Only the `%d, %u,  %x,  %c, %s, %p, %n and %%` conversions are supported.
* The suppression operator `*` is supported.
* The `%i, %o, and %X` conversions are *not* supported.
* The flags `-, +, space, 0 and #` are *not* supported.
* The width specification is *not* supported.
* The decimal precision is *not* supported.
* The length modifiers h, l (el) and L are *not* supported.
* The %f, %e, %E, %g and %G conversions are *not* supported.

Elfio Scan Conversions (-M option)
-----------------------------------
* The width specification is supported.
* The suppression operator `*` is supported.
* The `%d, %u, %x, %c, %s, %p, %n and %%` conversions are supported.
* The `%i and %o` conversions are *not* supported.
* The charset operators `%[...]` and `%[^...]` are *not* supported.
* The %f, %e, and %g conversions are *not* supported.

*Note:* The `__ELFIO__` macro is defined when the `-M` option is used to compile code.


Unsupported Stdlib Functions
----------------------------

The following functions were omitted from the ElfC stdlib C library.

* double atof(char\* s);
* long atol(char\* s);
* double strtod(char\* s, char\*\* endp);
* long strtol(char\* s, char\*\* endp, int base);
* unsigned long strtoul(char\* s, char\*\* endp, int base);
* long labs(long n);
* ldiv_t ldiv(long num, long denom);
* int system(char *s);

*Notes:*
* *All the long and double utility functions were omitted because these types are not supported in the current version.*
* *The math32 library provides equivalent functions as the long utility functions.*
* *The _atoi32_ function in math32 library provides equivalent function to _atol_.*
* *The _strtoi32_ function in math32 library provides equivalent function to _strtol_.*
* *The _divi32_ function in math32 library provides equivalent function to _ldiv_.*
* *The _absi32_ function in math32 library provides equivalent function to _labs_.*
* *The _strtou32_ function in mathu32 library provides equivalent function to _strtoul_.*
* *The system function has no equivalent in Elf/OS or Mini/DOS.*


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
*  The `lseek32` function uses the int32 struct type `off_t`and can be used for file sizes greater than 32KB, up to 2GB.
* `itox` and `itou` are available to convert int values to hexadecimal and unsigned integer ASCII strings.

Stdio Modified Functions
-------------------------
* `ftell` and `fseek` use an int type value for position, since long type is not supported.
* `fflush` is implemented as a NOP (No Operation) function.
* `tmpnam` creates a filename with form similar to `temp.00`.
* `fclose` will delete a temporary file created by `tmpfile` after closing it.
* Terminating a program by `abort` or without calling `fclose` to close a temporary file, may leave behind files created by `tmpfile`.
* `fseek32`, `fgetpos` and `fsetpos`f functions use the int32 struct type `pos_t` and can be used for files sizes greater than 32KB, up to 2GB.

Posix String Functions
----------------------------
* `strcasecmp` will compare two strings, ignoring case in both strings.
* `strcasestr` will locate a string within another string, ignoring case in both strings.
* `strdup` will allocate memory for a duplicate string, copy the characters, including the terminating null, into memory, and then return a pointer to the duplicate string.
* `strlcpy` will concatenate up to a specified number (length - 1) of characters and then append a null.  Unlike `strncat`, `strlcat` *always* appends a null.
* `strlcpy` will copy up to a specified number (length - 1) of characters and then append a null.  Unlike `strncpy`, `strlcpy` *always* appends a null.
* `strlwr` will lowercase a string in place.
* `strncasecmp` will compare up to n characters of two strings, ignoring case in both strings.
* `strndup` will allocate memory for a string of n characters, the copy up to n characters of the original string into memory, *always* terminating with a null, and then return a pointer to the duplicate string.
* `strnlen` will return the length of a string up to n, or n if the string is longer than n characters.
* `strnstr` locate a string within the first n characters of another string.
* `strrev` reverse the contents of a string in place.
* `strsep` locate in a string pointed to by \*str the first occurrence of any character in the separator string and replace it with a '\0'. The location of the next character after the separator is returned in *str, or NULL when the end of string is reached.
* `strupr` will uppercase a string in place.
* `strim` will remove any whitespace from the beginning or end of string in place.

Stdarg Macros
-----------------
* ElfC supports the variable argument macros as specified by the ANSI C C89/C90 specification.
* The variable argument macros use an argument pointer of type `va_list`, eg. `va_list ap;`
* The `va_start` should be called before `va_arg` is used to initialize the argument pointer.
* The `va_arg` macro can then be used to get the next argument.
* The `va_end` should be called after all variable arguments have been processed.
* The argument pointer is invalid after `va_end` is called.

```c
#include <stdio.h>
#include <stdarg.h>

/*
 * Function to print a number of variable arguments, specified by count
 */
int example(int count, ...) {
  int i, x;
  /* define argument pointer of type va_list */
  va_list ap;

  /* Set argument pointer to next argument after last */
  va_start(ap, count);

  /* print all the integer arguments */
  for (i=0; i < count; i++){
    /* get the next argument as integer */
    x = va_arg(ap, int);
    printf("arg %d = %d\n"i, x);
  }
  /* call va_end before function exits */
  va_end(ap);
}
```
Environment
-----------

The setenv(), getenv(), and unsetenv() functions are supported on Elf/OS and Mini/DOS. The src/examples folder includes a set of utilities for managing the environment from the command line.

* **export** This command is used to set a value for an environment variable. The command `export USER="John Q. Public"` sets the USER environment variable as shown. If no value is provided following the '=' sign, then the variable value is set to the empty string.

* **printenv** This command is used to print the current values of environment variables. The command `printenv X Y` would print the values of the X and Y variables on separate lines. If no variable names are specified, all of the environment variables and their values are printed.

* **unset** This command is used to delete environment variables. The command `unset X Y` will delete both the X and Y environment variables.

Assert Macro
--------------
* ElfC supports the `assert` macro as specified by the ANSI C C89/C90 specification.
* If the macro `NDEBUG` is defined the `assert` macro is ignored.
* The `__FILE__`, `__LINE__` and `__FUNCTION__` macros can be used as the file, line and function arguments, so the correct values are printed if the assertion is false.

Time Library
--------------

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

*Notes:*
* Many of the functions in C time library use static objects that may be over-written by other calls.

Unsupported Time Functions
---------------------------
The following functions were omitted from the ElfC time C library:

* clock_t clock(void) - there is no guaranteed time counter
* double difftime(time_t time2, time_t time1) - double is not supported by ElfC

You can calculate the difference in seconds between two time_t values using the subi32 function from the math32 library.

Local Timezone information
---------------------------
ElfC does not support the _locale.h_ header, so the following function may be used to set time zone information and daylight savings time information before calling other time functions.

* void timezone(char \*tzname, int tzoff_min, int tzdst)

*Notes:*
* `_tz_name_` is a string abbreviation for the time zone name, such as "EST" for US Eastern Standard Time.
* `_tz_offset_` is the offset from Universal Co-ordinated Time in seconds.  Offset values WEST of UTC should be negative, while offsets to the EAST are positive.
* `_tz_dst_` indicates if daylight savings time is in effect. It should be 1 if daylight savings time is in effect, and 0 if not.

The user may set the TZ environment variable to a POSIX-compliant description of the time zone.

### Format Breakdown

The standard format for a POSIX timezone string is:

*stdoffset[dst[offset][,start[/time],end[/time]]]]*

  * **std**: The name of the standard timezone (must be 3 or more alphabetic characters, like EST)
  * **offset**: The time value you must add to the local time to get UTC. Note: Signs are inverted compared to modern ISO-8601 standards (e.g., New York is UTC-5, so its POSIX offset is 5 or +5)
  * **dst**: The name of the daylight saving timezone (e.g., EDT). If missing, DST is not observed
  * **offset** (second occurrence): The DST offset. If missing, it defaults to 1 hour ahead of standard time
*.,start... ,end...: The specific dates and times when the switch into and out of DST occurs.

Common Examples

#### United States (Eastern Time):

  EST5EDT,M3.2.0,M11.1.0

  * EST5: Standard time is EST, which is 5 hours behind UTC (UTC = Local + 5)
  * EDT: Observes Daylight Saving Time (EDT)
  * M3.2.0: DST starts on the 3rd month (March), 2nd week, 0 day (Sunday)
  * M11.1.0: DST ends on the 11th month (November), 1st week, 0 day (Sunday)

#### United Kingdom (London):

  GMT0BST,M3.5.0/1,M10.5.0/2

  * GMT0: Standard time is GMT, 0 hours from UTC
  * BST: Observes British Summer Time
  * M3.5.0/1: Starts the last Sunday (5 means last week) of March at 1:00 AM
  * M10.5.0/2: Ends the last Sunday of October at 2:00 AM

There are currently two implementations of the tzset() function, which reads the TZ environment variable and sets the _tz variables for the current time zone. The `tzset_all` function is a full implementation of the POSIX standard and can interpret any time zone worldwide. The `tzset_us` function is much smaller and faster, but only handles US time zones. Additional implementations specific to other geographic locations may be added in the future. Code should call tzset, and a compiler command-line definitionis used to indicate which variant is desired for a program (e.g. elfc -D tzset=tzset_us timetest.c).

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

* char *_ctime(time_t *timer);
* time_t time(time_t *second);
* time_t timegm(struct tm *t);
* time_t mktime(struct tm *t);
* struct tm *gmtime(time_t *timer);
* struct tm *localtime(time_t *timer);
* char *asctime(struct tm *tp)
* int strftime(char *s, int smax, char *fmt, struct tm *tp);

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
<tr><td>%F</td><td>ISO date representation (%Y-%m-%d)</td></tr>
<tr><td>%H</td><td>hour (24-hour clock) as two digits with zero (00 to 23)</td></tr>
<tr><td>%I</td><td>hour (12-hour clock) as two digits with zero (01 to 12)</td></tr>
<tr><td>%j</td><td>day of year (001-366)</td></tr>
<tr><td>%m</td><td>month (01 to 12)</td></tr>
<tr><td>%M</td><td>minute (00 to 59)</td></tr>
<tr><td>%P</td><td>AM or PM</td></tr>
<tr><td>%p</td><td>am or pm</td></tr>
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


math32 Library
--------------
**The math32 library functions use the following structure and type.**

```c
struct int32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

/* 32-bit signed number represented as two 16-bit values */
typedef struct int32 int32_t;

struct uint32 {
    unsigned int low;   /* Lower 16 bits */
    unsigned int high;  /* Upper 16 bits */
};

/* 32-bit unsigned number represented as two 16-bit values */
typedef struct uint32 uint32_t;
```
*Note: `off_t` in `<stdlib.h>` and `pos_t` in `<stdio.h>` are also defined by struct int32 typedefs.*

**The following signed 32-bit functions are supported in the ElfC math32 library.**

* _absi32(a)_ - 32-bit absolute value of a
* _addi32(a, b)_ - 32-bit addition: returns a + b
* _subi32(a, b)_ - 32-bit subtraction: returns a - b
* _muli32(a, b)_ - 32-bit multiplication: returns a *
* _muli32x16(a, int b)_ - 32 x 16-bit multiplication: returns a * b
* _cmpi32(a, b)_ - Compare two 32-bit numbers, returns -1 if a < b, 0 if a == b or 1 if a > b
* _shli32(a, int n)_ - Shift 32-bit number left by n bits
* _shri32(a, int n)_ - Shift 32-bit number right by n bits
* _asri32(a, int n)_ - Arithmetic shift right by n bits
* _divi32(a, b, *rem)_ - 32-bit division: returns quotient, remainder in *rem
* _i32_from_int(int n)_ - Convert 16-bit number to 32-bit number with sign extension
* _int_from_i32(n)_ - Truncate 32-bit number to 16-bit integer
* _negi32(a)_ - Negate a 32-bit number
* _atoi32(char *str)_ - Convert a string into 32-bit integer
* _char *i32toa(a, char *str)_ - Convert 32-bit integer to string, returns pointer to beginning of string
* _strtoi32(const char *nptr, char **endptr, int base)_ - Convert string to 32-bit integer
* _int_from_i32(n)_ - Cast 32-bit to 16-bit signed integer
* _make_i32(unsigned int high, unsigned int low)_ Create 32-bit integer from high and low words
*Note: all variables and return values are type `int32_t`, unless typed differently*

**The following unsigned 32-bit functions are supported in the ElfC math32 library.**

* _addu32(a, b)_ - 32-bit unsigned addition: returns a + b
* _subu32(a, b)_ - 32-bit unsigned subtraction: returns a - b
* _mulu32(a, b)_ - 32-bit unsigned multiplication: returns a *
* _mulu32x16(a, int b)_ - 32 x 16-bit unsigned multiplication: returns a * b
* _cmpi32(a, b)_ - Compare two 32-bit unsigned numbers, returns -1 if a < b, 0 if a == b or 1 if a > b
* _shlu32(a, int n)_ - Shift 32-bit unsigned number left by n bits
* _shru32(a, int n)_ - Shift 32-bit unsigned number right by n bits
* _divu32(a, b, *rem)_ - 32-bit unsigned division: returns quotient, remainder in *rem
* _u32_from_int(int n)_ - Convert 16-bit number to unsigned 32-bit number
* _uint_from_u32(n)_ - Truncate unsigned 32-bit number to unsigned 16-bit integer
* _atou32(char *str)_ - Convert a string into unsigned 32-bit integer
* _char *u32toa(a, char *str)_ - Convert 32-bit unsigned integer to string, returns pointer to beginning of string
* _strtou32(const char *nptr, char **endptr, int base)_ - Convert string to 32-bit unsigned integer
* _uint_from_u32(n)_ - Cast 32-bit to 16-bit unsigned integer
* _make_u32(unsigned int high, unsigned int low)_ Create 32-bit unsigned integer from high and low words

*Note: all variables and return values are type `uint32_t`, unless typed differently*

**The following functions for converting between signed and unsigned are supported in the ElfC math32 library.**

* _u32_from_i32(v)_ - Convert signed 32-bit to unsigned 32-bit
* _i32_from_u32(v)_ - Convert unsigned 32-bit to signed 32-bit





Float32 Library
----------------
**The float32 library functions use the following structures and types.**

```c
struct float32 {
    unsigned int low;   /* low word */
    unsigned int high;  /* high word*/
};

/* 32-bit single precision floating point numbers */
typedef struct float32 float32_t;
```
**Special Values**
The float32 library defines the following special values
* `NaN` - Not a Number, when a value is out of the defined domain
* `+Inf` - Positive Infinity $+\infty $, Overflow in the positive range
* `-Inf` - Negative Infinity $-\infty $, Overflow in the negative range

Not a number or `NaN` is returned under the following conditions.
* The result of $0\div0$, $0 \times \pm\infty $ or $\pm\infty \div\pm\infty $
* The result of $\pm\infty  + \mp\infty $ or $\pm\infty  - \pm\infty $
* The result of `sqrt(x)` when $x \lt 0$
* The result of `logf(x)` when $x \lt 0$
* The result of `powf(b,p)` when $b \lt 0$ or $b \eq 0$ and $p \leq 0$

When `NaN` is returned `errno` is set to `EDOM` (domain error).

When the result of a function exceeds the floating point range `+Inf` or `-Inf` is returned.
* `+Inf` is returned when positive overflow occurs in the result, x $\gt$ FLT_MAX
* `-Inf` is returned when negative overflow occurs in the result, x $\lt$ -FLT_MAX

When '+Inf' or `-Inf` is returned `errno` is set to `ERANGE` (out of range error).

Underflow occurs when the absolute value of the result is less than the smallest absolute floating point value FLT_MIN.

* Zero is returned when underflow occurs.
* Float32 does not use a negative zero value or sub-normal values.
* Instead, Zero is always considered unsigned and underflow is not considered an error.
* This is called _store zero_ or _flush to zero_ method.

**The float32 library provides the following math functions**

**Arithmetic functions**
* float32_t _absf(float32_t a)_ - return the absolute value of a, $\lvert a \rvert$
* float32_t _addf(float32_t a, float32_t b)_ - return $a + b$
* float32_t _divf(float32_t a, float32_t b)_- return $a \div b$
* float32_t _mulf(float32_t a, float32_t b)_ - return $a \times b$
* float32_t _subf(float32_t a, float32_t b)_ - return $a - b$
* float32_t _negf(float32_t a)_ - return $-a$
* float32_t _invf(float32_t a)_ - return the reciprocal $\frac{1}{a}$
* float32_t _fmodf(float32_t a, float32_t b)_ - return $a \bmod b$

Note: If either `a` or `b` is `NaN` then the result is `NaN` and `errno` is set to `EDOM`.

**Comparison functions**
* int _eqf(float32_t a, float32_t b)_ - return true if $a \eq b$
* int _gtf(float32_t a, float32_t b)_ - return true if $a \gt b$
* int _gtef(float32_t a, float32_t b)_ - return true if $a \geq b$
* int _ltf(float32_t a, float32_t b)_ - return true if $a \lt b$
* int _ltef(float32_t a, float32_t b)_ - return true if $a \leq b$
* int _nef(float32_t a, float32_t b)_ - return true if $a \neq b$

Note:
* If either `a` or `b` is 'NaN', then _eqf_, _gtf_, _gte_, _ltf_ and _ltef_ all return `false`.
* If either `a` or `b` is `NaN` then the _nef_ function returns `true`.
* In particular, note that _nef(NaN, NaN)_ will return *false*.
* `+Inf` is considered equal to `+Inf`
* `+Inf` is greater than any other number.
* `-Inf` is considered equal to `-Inf`
* `-Inf` is less than any other number.

The following table shows the results of comparison functions with special values. The value `x` represents any other number.

<table>
<tr><th>a<th>b<th>eqf</th><th>neqf</th><th>gtef</th><th>gtf</th><th>ltef</th><th>ltf</th></tr>
<tr><td>NaN</td><td>NaN</td><td>false</td><td>true</td><td>false</td><td>false</td><td>false</td><td>false</td></tr>
<tr><td>NaN</td><td>x</td><td>false</td><td>true</td><td>false</td><td>false</td><td>false</td><td>false</td></tr>
<tr><td>x</td><td>NaN</td><td>false</td><td>true</td><td>false</td><td>false</td><td>false</td><td>false</td></tr>
<tr><td>+Inf</td><td>+Inf</td><td>true</td><td>false</td><td>true</td><td>false</td><td>true</td><td>false</td></tr>
<tr><td>+Inf</td><td>x</td><td>false</td><td>true</td><td>true</td><td>true</td><td>false</td><td>false</td></tr>
<tr><td>x</td><td>+Inf</td><td>false</td><td>true</td><td>false</td><td>false</td><td>true</td><td>true</td></tr>
<tr><td>-Inf</td><td>-Inf</td><td>true</td><td>false</td><td>true</td><td>false</td><td>true</td><td>false</td></tr>
<tr><td>-Inf</td><td>x</td><td>false</td><td>true</td><td>false</td><td>false</td><td>true</td><td>true</td></tr>
<tr><td>x</td><td>-Inf</td><td>false</td><td>true</td><td>true</td><td>true</td><td>false</td><td>false</td></tr>
</table>

**Tests for Special values**
* _isNan(a)_ - return true if a is Not a Number `NaN`, the sign bit is ignored
* _isInf(a)_ - return true if a is `+Inf` or `-Inf`
* _isZero(a)_ - return true if a is `0`, the sign bit is ignored

**Conversion functions**
* void _ftoa(float32_t fp1, char \*s)_ - convert a floating point number into an ASCII string
* int32_t _ftoi32(float32_t a)_ - convert a floating point number into a 32-bit integer
* int _ftoi(float32_t a)_ - convert a floating point number into an integer
* float32_t _atof(char \*s)_ - convert an ASCII string into floating point number
* float32_t _itof(int i)_ - convert an int value into floating point number
* float32_t _i32tof(int32_t i)_ - convert a 32-bit integer into floating point number

**Trig functions**
* float32_t _sinf(float32_t a)_ - return the $\sin(a)$ in radians
* float32_t _cosf(float32_t a)_ - return the $\cos(a)$ in radians
* float32_t _tanf(float32_t a)_ - return the $\tan(a)$ in radians
* float32_t _asinf(float32_t a)_ - return the $\arcsin(a)$ in the range of ($\frac{-\pi}{2}$, $\frac{+\pi}{2}$, the domain of a is (-1, 1)
* float32_t _acosf(float32_t a)_- return the $\arccos(a)$ in the range of (0, $\pi$), the domain of a is (-1, 1)
* float32_t _atanf(float32_t a)_- return the $\arctan(a)$ in the range of ($\frac{-\pi}{2}$, $\frac{+\pi}{2}$), the domain of a is (-1, 1)
* float32_t _atan2f(float32_t y, float32_t x)_ - return the $\arctan(\frac{y}{x})$ in the range of ($-\pi$, $+\pi$).

**Angle conversion functions**
* float32_t _areducef(float32_t a)_ - reduce an angle to range of ($-\pi$, $\pi) radians
* float32_t _rad2degf(float32_t a)_ - convert an angle in radians to degrees
* float32_t _deg2radf(float32_t a)_ - convert an angle in degrees to radians

**Rounding functions**
* float32_t _truncf(float32_t a)_ - return the whole number part of a, as a floating point number
* float32_t _modf(float32_t a, float32_t \*ip)_ - split a into an integer and fractional parts, each with the same size as a. Store the integer part in \*ip and return the fractional part.
* float32_t _fracf(float32_t a)_ - return the fractional part of a, as a floating point number
* float32_t _ceilf(float32_t a)_ - return the smallest integer not less than a, as a floating point number
* float32_t _floorf(float32_t a)_ - return the largest integer not greater than a, as a floating point number
* float32_t _roundf(float32_t a)_ - return a rounded to the nearest integer, as a floating point number
* float32_t _frexpf(float32_t a, int \*exp)_ - split a into a normalized fraction from (0.5, 1) and a power of two.  Set *exp to the power of 2 and return the normalized fraction.
* float32_t _ldexpf(float32_t m, int n)_ - return $a\times2^n$
* float32_t _zflushf(float32_t a, float32_t eps)_ - If $(a)$ $\leq$ $\epsilon$, return 0, else return a.

**Logarithmic and Power Functins**
* float32_t _expf(float32_t a)_ - return the exponential function $\exp^a$
* float32_t _logf(float32_t a)_ - return the natural logarithm function $\ln(a)$, where $a \gt 0$
* float32_t _log2f(float32_t a)_- return the base 2 logarithm function $\log_2(a)$, where $a \gt 0$
* float32_t _log10f(float32_t a)_- return the common logarithm function $\log_10(a)$, where $a \gt 0$
* float32_t _sqrtf(float32_t a)_ - return the square root of a, where $a $geq 0$
* float32_t _powf(float32_t b, float32_t p)_ - return base b to the power p $b^p$, where $b \gt 0$ or $b \eq 0$ and $p \gt 0$.
* float32_t _hypotf(float32_t a, float32_t b)_ - return the hypotenuse of a and b $\sqrt{a^2 + b^2}$
* float32_t _sinhf(float32_t a)_ - return the $\hypsine(a)$
* float32_t _coshf(float32_t a)_ - return the $\hypcosine(a)$
* float32_t _tanhf(float32_t a)_ - return the $\hyptangent(a)$

Pre-Defined Macros
-------------------
* The `__ELFC__` macro is defined to identify the compiler for conditional compilation.
* If `_ELFCLIB_` is defined, C code is compiled for an Elf/OS library procedure.
* If `_STGROM_`  is defined, assembly code to support STG ROM breakpoints is created.
* If `_MAXMON_` is defined, assembly code to support MAXMON ROM breakpoints is created.
* `BRKPT` inserts assembly code in the code file to invoke the break point handler, when `_STGROM_` or `_MAXMON_` is defined.
* `__LINE__` inserts the current line number in the code file.
* `__FILE__` insert the current file name in the code file.
* `__FUNCTION__` insert the current function name in the code file.
* If `NDEBUG` is defined, the `assert` macro is ignored.
* The <assert.h> header file defines the `assert` macro.
* The <stdarg.h> header file defines the `va_list` type and the `va_start`, `va_arg` and `va_end` macros.
* The <stdio.h> header file defines the `getchar` and `putchar` macros.
* The <stdlib.h> header file defines the `abs`, `MIN` and `MAX` macros.
* The `__ELFIO__` macro is defined when the `-M` option is used to compile code.

*Note: The `__LINE__`, `__FILE__`, `__FUNCTION__`  and `__ELFIO__` macros begin and end with **two** underscores.*

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

Compiler Options
----------------

<table>
<tr><th>Option</th><th>Description</th></tr>
<tr><td>-c </td><td>compile and assemble only, do not link</td></tr>
<tr><td>-d opt</td><td>activate debug option OPT, ? = list</td></tr>
<tr><td>-o file</td><td>write linker output to FILE</td></tr>
<tr><td>-t </td><td>test only, generate no code</td></tr>
<tr><td>-v </td><td>verbose output</td></tr>
<tr><td>-D m=v</td><td>define macro M with optional value V</td></tr>
<tr><td>-L </td><td>compile and assemble a library object file</td></tr>
<tr><td>-N </td><td>do not link stdlib and stdio by default</td></tr>
<tr><td>-M </td><td>use smaller elfstd and elfio libraries</td></tr>
<tr><td>-P </td><td>print expanded macro text</td></tr>
<tr><td>-S </td><td>compile to assembly language</td></tr>
<tr><td>-V </td><td>print version and exit</td></tr>
<tr><th colspan="2">Debug Options</th></tr>
<tr><td>-d gsym</td><td>dump global symbols</td></tr>
<tr><td>-d lsym</td><td>dump local symbols</td></tr>
<tr><td>-d stat</td><td>print usage statistics</td></tr>
<tr><td>-d tree</td><td>dump abstract symbol tree (AST)</td></tr>
</table>

Details about the ElfC internal implementation can be found on the [ELFC Internal Information](INSIDE.md) page.
