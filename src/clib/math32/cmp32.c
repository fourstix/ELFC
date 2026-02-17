#define _ELFCLIB_
#include <math32.h>

/* Compare two 32-bit numbers */
/* Returns: -1 if a < b, 0 if a == b, 1 if a > b */
int cmp32(int32 *a, int32 *b) {
    if (a->high < b->high) return -1;
    if (a->high > b->high) return 1;
    if (a->low < b->low) return -1;
    if (a->low > b->low) return 1;
    return 0;
}
