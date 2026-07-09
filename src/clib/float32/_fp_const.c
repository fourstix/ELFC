#define _ELFCLIB_
#include <float32.h>

/*
 * floating point values used in C library functions
 */
float32_t _fp_half = {FP_DOT5_LO, FP_DOT5_HI};
float32_t _fp_one = {FP_ONE_LO, FP_ONE_HI};
float32_t _fp_negone = {FP_ONE_LO, FP_ONE_HI | FP_SIGN};

/* trig values */
float32_t _fp_2pi = {FP_2PI_LO, FP_2PI_HI};
float32_t _fp_pi  = {FP_PI_LO, FP_PI_HI};
float32_t _fp_negpi  = {FP_PI_LO, FP_PI_HI | FP_SIGN};

/* Conversion constants for angles */
float32_t _fp_rad2deg = {FP_RAD_DEG_LO, FP_RAD_DEG_HI};
float32_t _fp_deg2rad = {FP_DEG_RAD_LO, FP_DEG_RAD_HI};

/* flush to zero value for trig functions */
float32_t _fp_epsilon = {FP_RND_0_L0, FP_RND_0_HI};

/* domain limits for atanf argument */
float32_t _fp_atan_dmax = {FP_AT_MAX_LO, FP_AT_MAX_HI};
float32_t _fp_atan_dmin = {FP_AT_MAX_LO, FP_AT_MAX_HI | FP_SIGN};

/* maximum exponent for overflow ln(FLT_MAX) */
float32_t _fp_exp_max = {FP_E_MAX_LO, FP_E_MAX_HI};
float32_t _fp_exp_min = {FP_E_MAX_LO, FP_E_MAX_HI | FP_SIGN};

/* Logarithm constants */
float32_t _fp_ln2 = {FP_LN_2_LO, FP_LN_2_HI};
float32_t _fp_ln10 = {FP_LN_10_LO, FP_LN_10_HI};

/* Conversion constants */
float32_t _fp_ten   = {FP_TEN_LO, FP_TEN_HI};
float32_t _fp_two   = {FP_TWO_LO, FP_TWO_HI};
float32_t _fp_10p5  = {FP_10P5_LO, FP_10P5_HI};
float32_t _fp_10n5  = {FP_10N5_LO, FP_10N5_HI};
float32_t _fp_round = {FP_RND45_LO, FP_RND45_HI};

void _fp_const() {
 /* required entry point */
}
