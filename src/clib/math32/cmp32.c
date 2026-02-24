#define _ELFCLIB_
#include <math32.h>

/* Compare two 32-bit numbers */
/* Returns: -1 if a < b, 0 if a == b, 1 if a > b */
int cmp32(int32_t *a, int32_t *b) {
    int signed_high_a;
    int signed_high_b;
    
    if (a->high != b->high) {
        // Since high words contain the sign bit, we need to handle the
        // signed comparison manually. We cast the high words to a 
        // *signed* 16-bit type for the comparison, as a direct unsigned 
        // comparison can lead to issues.
        signed_high_a = (int)a->high;
        signed_high_b = (int)b->high;

        if (signed_high_a < signed_high_b) {
            return -1;
        } else {
            return 1;
        }
    } else {
        // High words are equal, compare low words as unsigned 16-bit integers
        if (a->low < b->low) {
            return -1;
        } else if (a->low > b->low) {
            return 1;
        } else {
            // Both high and low words are equal
            return 0;
        }
    }
}
