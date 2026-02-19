#define _ELFCLIB_
#include <math32.h>
#include <stdbool.h>

#pragma             extrn Cneg32
#pragma             extrn Cadd32

/* 32-bit multiplication: result = a * b */
int32_t mul32(int32_t *a, int32_t *b) {
    int32_t product;
    int32_t multiplier;
    int32_t multiplicand;
    int i;
    bool negative = false;

    if (a->high & 0x8000) {
        multiplier = neg32(a);
        negative = !negative;
    }
    else {
        multiplier.high = a->high;
        multiplier.low = a->low;
    }

    if (b->high & 0x8000) {
        multiplicand = neg32(b);
        negative = !negative;
    }
    else {
        multiplicand.high = b->high;
        multiplicand.low = b->low;
    }

    product.high = 0;
    product.low = 0;

    // Iterate through all 32 bits of the multiplier
    for (i = 0; i < 32; i++) {
        // Check the least significant bit of the multiplier
        if (multiplier.low & 0x0001) {
            product = add32(&product, &multiplicand);
        }

        // Right shift the multiplier
        // This requires careful handling across the 16-bit boundary
        multiplier.low >>= 1;
        if (multiplier.high & 0x0001) {
            multiplier.low |= 0x8000;
        }
        multiplier.high >>= 1;

        // Left shift the multiplicand
        // This requires careful handling across the 16-bit boundary
        // We only care about the lower 32 bits for the result structure
        multiplicand.high <<= 1;
        if (multiplicand.low & 0x8000) {
            multiplicand.high |= 0x0001; // Carry into the low bit of high
        }
        multiplicand.low <<= 1;
    }

    if (negative) {
        product = neg32(&product);
    }

    return product;
}
