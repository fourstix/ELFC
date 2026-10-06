/*
 * unsetenv.c
 *
 * Remove an environment variable from the on-disk store.
 * The store is the one used by the ELF-DOS commands, and is written
 * by the env module of the ELF-DOS SDK, which is part of this library.
 *
 * Returns 0 on success (including when the variable was not set to
 * begin with, matching the standard unsetenv), -1 on error.
 */
#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn env_unsetenv

/* the sdk keeps its data in a separate procedure, which the linker */
/* only takes from a library when it is named as required */
#pragma           .link .requires _env_data

int unsetenv(const char *name)
{
    int result;

    if (name == NULL)
        return -1;

    asm("         gosub s_lget16  ; get the name argument ");
    asm("           dw 0          ; get from argument stack");
    asm("         copy ra, rf     ; copy name string to buffer pointer");
    _KSAVE
    asm("         call env_unsetenv ; remove the variable");
    _KRESTORE
    _KRESULT
    asm("         gosub s_lset16  ; set the result value ");
    asm("           dw -2         ; in the local variable on the stack");

    return result;
}
