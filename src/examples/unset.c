/*
 * unset.c
 *
 * Command-line utility: unset VAR [VAR ...]
 *
 * Removes one or more environment variables, mirroring the shell
 * builtin. Each command-line argument is treated as a separate
 * variable name to remove. Invalid names (e.g. containing '=') and
 * variables that are not currently set are silently ignored, since
 * that is not an error condition for this command — the end state
 * (variable absent) is what was requested either way.
 *
 * Always exits with status 0.
 */

#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 1; i < argc; i++) {
        unsetenv(argv[i]);   /* return value ignored: invalid/unset
                               * names are not an error for this
                               * command */
    }

    return 0;
}
