/*
 * getenv.c
 *
 * Look up an environment variable's value in the on-disk store.
 * The store is the one used by the ELF-DOS commands, and is read
 * by the env module of the ELF-DOS SDK, which is part of this library.
 *
 * Like the standard C library, returns a pointer to an internal
 * static buffer that remains valid until the next call to getenv,
 * setenv or unsetenv, so the value should be copied out by the
 * caller if it must persist.
 */
#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn env_getenv

/* the sdk keeps its data in a separate procedure, which the linker */
/* only takes from a library when it is named as required */
#pragma           .link .requires _env_data

char *getenv(const char *name)
{
    char *value;

    if (name == NULL)
        return NULL;

    asm("         gosub s_lget16  ; get the name argument ");
    asm("           dw 0          ; get from argument stack");
    asm("         copy ra, rf     ; copy name string to buffer pointer");
    _KSAVE
    asm("         call env_getenv ; look up the variable");
    _KRESTORE
    asm("         copy rf, ra     ; pointer is NULL if not found");
    asm("         gosub s_lset16  ; set the value pointer ");
    asm("           dw -2         ; in the local variable on the stack");

    return value;
}
