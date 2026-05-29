#ifndef STDINT_H_
#define STDINT_H_

/* 7.18.1.1 Exact-width integer types */
typedef char int8_t;
typedef unsigned char uint8_t;
typedef int int16_t;
typedef unsigned int uint16_t;

/* 7.18.1.2 Minimum-width integer types */
/*! smallest signed integer type with width of at least 8 */
typedef int8_t int_least8_t;

/*! smallest signed integer type with width of at least 16 */
typedef int16_t int_least16_t;

/*! smallest unsigned integer type with width of at least 8 */
typedef uint8_t uint_least8_t;

/*! smallest unsigned integer type with width of at least 16 */
typedef uint16_t uint_least16_t;

/* 7.18.1.3 Fastest-width integer types */
/*! fastest signed integer type with width of at least 8 */
typedef int8_t int_fast8_t;

/*! fastest signed integer type with width of at least 16 */
typedef int16_t int_fast16_t;

/*! fastest unsigned integer type with width of at least 8 */
typedef uint8_t uint_fast8_t;

/*! fastest unsigned integer type with width of at least 16 */
typedef uint16_t uint_fast16_t;

/* 7.18.1.4 Integer types capable of holding object pointers */
typedef int intptr_t;
typedef unsigned int uintptr_t;

/* 7.18.1.5 Greatest-width integer types */
typedef int intmax_t;
typedef unsigned int uintmax_t;

/* 7.18.2 Limits of specified-width integer types:
 *   These #defines specify the minimum and maximum limits
 *   of each of the types declared above.
 */

/* 7.18.2.1 Limits of exact-width integer types */
/*! Expands to 127. Maximum value of an object of type int8_t */
#define INT8_MAX 127

/*! Expands to 32767. Maximum value of an object of type int16_t */
#define INT16_MAX 32767

/*! Expands to -128. Minimum value of an object of type int8_t */
#define INT8_MIN -128

/*! Expands to -32768. Minimum value of an object of type int16_t */
#define INT16_MIN -32768

/*! Expands to 255. Maximum value of an object of type uint8_t */
#define UINT8_MAX 255

/*! Expands to 65535. Maximum value of an object of type uint16_t */
#define UINT16_MAX 65535

/* 7.18.2.2 Limits of minimum-width integer types */
/*! Minimum value of an object of type int_least8_t */
#define INT_LEAST8_MIN INT8_MIN

/*! Minimum value of an object of type int_least16_t */
#define INT_LEAST16_MIN INT16_MIN

/*! Minimum value of an object of type uint_least8_t */
#define UINT_LEAST8_MIN UINT8_MIN

/*! Minimum value of an object of type uint_least16_t */
#define UINT_LEAST16_MIN UINT16_MIN

/*! Maximum value of an object of type uint_least8_t */
#define INT_LEAST8_MAX INT8_MAX

/*! Maximum value of an object of type int_least16_t */
#define INT_LEAST16_MAX INT16_MAX

/*! Maximum value of an object of type uint_least8_t */
#define UINT_LEAST8_MAX UINT8_MAX

/*! Maximum value of an object of type uint_least16_t */
#define UINT_LEAST16_MAX UINT16_MAX

/* 7.18.2.3 Limits of fastest minimum-width integer types */
/*! Minimum value of an object of type int_fast8_t */
#define INT_FAST8_MIN INT8_MIN

/*! Minimum value of an object of type int_fast16_t */
#define INT_FAST16_MIN INT16_MIN

/*! Maximum value of an object of type int_fast8_t */
#define INT_FAST8_MAX INT8_MAX

/*! Maximum value of an object of type int_fast16_t */
#define INT_FAST16_MAX INT16_MAX

/*! Minimum value of an object of type uint_fast8_t */
#define UINT_FAST8_MIN UINT8_MIN

/*! Minimum value of an object of type uint_fast16_t */
#define UINT_FAST16_MIN UINT16_MIN

/*! Maximum value of an object of type uint_fast8_t */
#define UINT_FAST8_MAX UINT8_MAX

/*! Maximum value of an object of type uint_fast16_t */
#define UINT_FAST16_MAX UINT16_MAX

/*! Minimum value of an object of type intptr_t */
#define INTPTR_MIN INT16_MIN

/*! Maximum value of an object of type intptr_t */
#define INTPTR_MAX INT16_MAX

/*! Maximum value of an object of type uintptr_t  */
#define UINTPTR_MAX UINT16_MAX

/*! Minimum value of an object of type ptrdiff_t */
#define PTRDIFF_MIN INT16_MIN

/*! Maximum value of an object of type ptrdiff_t */
#define PTRDIFF_MAX INT16_MAX

/*! Minimum value of an object of type intmax_t */
#define INTMAX_MIN INT16_MIN

/*! Maximum value of an object of type intmax_t  */
#define INTMAX_MAX INT16_MAX

/*! Maximum value of an object of type uintmax_t  */
#define UINTMAX_MAX UINT16_MAX

/*! Maximum value of object of size_t type */
#ifndef SIZE_MAX
#define SIZE_MAX UINT16_MAX
#endif

#endif /* STDINT_H_ */
