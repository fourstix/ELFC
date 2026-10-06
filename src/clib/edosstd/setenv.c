/*
 * setenv.c
 *
 * Set (or update) an environment variable in the on-disk store.
 * The store is the one used by the ELF-DOS commands, and is written
 * by the env module of the ELF-DOS SDK, which is part of this library.
 *
 * Returns 0 on success, -1 on error (matching the standard setenv).
 */
#define _ELFCLIB_
#include <stdlib.h>
#include "edos.h"

#pragma             extrn env_setenv

/* the sdk keeps its data in a separate procedure, which the linker */
/* only takes from a library when it is named as required */
#pragma           .link .requires _env_data

int setenv(const char *name, const char *value, int overwrite)
{
    int result;

    if (name == NULL || value == NULL)
        return -1;

    asm("         gosub s_lget16  ; get the name argument ");
    asm("           dw 0          ; get from argument stack");
    asm("         copy ra, rf     ; copy name string to buffer pointer");
    asm("         gosub s_lget16  ; get the value argument ");
    asm("           dw 2          ; get from argument stack");
    asm("         copy ra, rd     ; copy value string to buffer pointer");
    asm("         gosub s_lget16  ; get the overwrite argument ");
    asm("           dw 4          ; get from argument stack");
    _KSAVE
    asm("         glo  ra         ; D is non-zero to overwrite");
    asm("         lbnz se_set     ; so use the lo byte if it is set");
    asm("         ghi  ra         ; otherwise the hi byte decides");
    asm("se_set:  call env_setenv ; set the variable");
    _KRESTORE
    _KRESULT
    asm("         gosub s_lset16  ; set the result value ");
    asm("           dw -2         ; in the local variable on the stack");

    return result;
}
