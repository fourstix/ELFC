/*
 * export.c
 *
 * Command-line utility: export VAR=value
 *
 * Sets an environment variable, mirroring the shell builtin's basic
 * usage. Only the first command-line argument is used; any
 * additional arguments are ignored.
 *
 * If the argument contains no '=' at all, the command does nothing
 * and exits successfully (this mirrors the shell builtin's behaviour
 * of "export EXISTING_VAR" simply marking an existing shell variable
 * for export without changing its value; since this implementation
 * has no separate shell-variable concept to mark, a bare name with
 * no '=' has no effect here).
 *
 * Otherwise, the first '=' separates the name from the value (so
 * values may themselves contain '=' characters). The name portion
 * must be a valid identifier: non-empty, starting with a letter or
 * underscore (not a digit), and containing only letters, digits,
 * and underscores thereafter. If it is not, the program prints:
 *     ARGUMENT: not a valid identifier
 * (where ARGUMENT is the full original argument, with '=' restored)
 * and exits with a non-zero status.
 *
 * Always overwrites any existing value for the variable, matching
 * the shell builtin's normal behaviour.
 *
 * Exit status: 0 on success (including the no-'=' no-op case) or if
 * no argument was given; 1 if the name is not a valid identifier;
 * 2 if setenv() itself fails.
 */

#include <stdlib.h>

static int is_valid_identifier(const char *name)
{
    const char *p;

    if (*name == '\0')
        return 0;

    if (!((*name >= 'A' && *name <= 'Z') ||
          (*name >= 'a' && *name <= 'z') ||
          (*name == '_')))
        return 0;               /* must not start with a digit */

    for (p = name + 1; *p != '\0'; p++) {
        if (!((*p >= 'A' && *p <= 'Z') ||
              (*p >= 'a' && *p <= 'z') ||
              (*p >= '0' && *p <= '9') ||
              (*p == '_')))
            return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char *assignment;
    char *p;
    char *value;

    if (argc < 2)
        return 0;

    assignment = argv[1];

    /* find the first '=' */
    p = assignment;
    while (*p != '\0' && *p != '=')
        p++;

    if (*p != '=')
        return 0;                /* no '=' at all: no-op, not an error */

    *p = '\0';                   /* split: assignment is now the name */
    value = p + 1;

    if (!is_valid_identifier(assignment)) {
        /* restore the '=' so the printed argument matches exactly
         * what the user typed */
        *p = '=';
        putstr(assignment);
        puts(": not a valid identifier");
        return 1;
    }

    if (setenv(assignment, value, 1) != 0)
        return 2;

    return 0;
}
