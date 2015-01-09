/*-
 * "minimal" replacement for ISO C99 "stdint.h" header file (not com-
 * plete yet, but pretty near, with some ISO C11 sprinkled in for fun
 */

#ifndef	_STDINT_H
#define	_STDINT_H "$MirOS$"

/* get {,u,u_}int8_t definitions and stuff */

#include <machine/types.h>

/* define extended integer types to be the same as basic ones for now */

typedef	int8_t		int_least8_t;
typedef	int16_t		int_least16_t;
typedef	int32_t		int_least32_t;
typedef	int64_t		int_least64_t;
typedef	uint8_t		uint_least8_t;
typedef	uint16_t	uint_least16_t;
typedef	uint32_t	uint_least32_t;
typedef	uint64_t	uint_least64_t;

typedef	int8_t		int_fast8_t;		/* probably int? */
typedef	int16_t		int_fast16_t;		/* probably int? */
typedef	int32_t		int_fast32_t;
typedef	int64_t		int_fast64_t;
typedef	uint8_t		uint_fast8_t;		/* probably unsigned? */
typedef	uint16_t	uint_fast16_t;		/* probably unsigned? */
typedef	uint32_t	uint_fast32_t;
typedef	uint64_t	uint_fast64_t;

/* we don't have 128 bits yet ;-) */

typedef	int64_t		intmax_t;
typedef	uint64_t	uintmax_t;


#if (!defined(__cplusplus)) || defined(__STDC_LIMIT_MACROS)

/* basic types */

#define	INT8_MIN	(-0x7F-1)
#define	INT8_MAX	0x7F
#define	UINT8_MAX	0xFFU

#define	INT16_MIN	(-0x7FFF-1)
#define	INT16_MAX	0x7FFF
#define	UINT16_MAX	0xFFFFU

#define	INT32_MIN	(-0x7FFFFFFFL-1)
#define	INT32_MAX	0x7FFFFFFFL
#define	UINT32_MAX	0xFFFFFFFFUL

#define	INT64_MIN	(-0x7FFFFFFFFFFFFFFFLL-1)
#define	INT64_MAX	0x7FFFFFFFFFFFFFFFLL
#define	UINT64_MAX	0xFFFFFFFFFFFFFFFFULL

/* minimum types - same as basic types for now */

#define	INT_LEAST8_MIN		INT8_MIN
#define	INT_LEAST8_MAX		INT8_MAX
#define	UINT_LEAST8_MAX		UINT8_MAX

#define	INT_LEAST16_MIN		INT16_MIN
#define	INT_LEAST16_MAX		INT16_MAX
#define	UINT_LEAST16_MAX	UINT16_MAX

#define	INT_LEAST32_MIN		INT32_MIN
#define	INT_LEAST32_MAX		INT32_MAX
#define	UINT_LEAST32_MAX	UINT32_MAX

#define	INT_LEAST64_MIN		INT64_MIN
#define	INT_LEAST64_MAX		INT64_MAX
#define	UINT_LEAST64_MAX	UINT64_MAX

/* fastest types - same as basic types for now */

#define	INT_FAST8_MIN		INT8_MIN
#define	INT_FAST8_MAX		INT8_MAX
#define	UINT_FAST8_MAX		UINT8_MAX

#define	INT_FAST16_MIN		INT16_MIN
#define	INT_FAST16_MAX		INT16_MAX
#define	UINT_FAST16_MAX		UINT16_MAX

#define	INT_FAST32_MIN		INT32_MIN
#define	INT_FAST32_MAX		INT32_MAX
#define	UINT_FAST32_MAX		UINT32_MAX

#define	INT_FAST64_MIN		INT64_MIN
#define	INT_FAST64_MAX		INT64_MAX
#define	UINT_FAST64_MAX		UINT64_MAX

/* pointer types - machdep */

#ifdef	__LP64__
#define	INTPTR_MIN		INT64_MIN
#define	INTPTR_MAX		INT64_MAX
#define	UINTPTR_MAX		UINT64_MAX
#else
#define	INTPTR_MIN		INT32_MIN
#define	INTPTR_MAX		INT32_MAX
#define	UINTPTR_MAX		UINT32_MAX
#endif

/* largest integer - 64 bit for now */

#define	INTMAX_MIN		INT64_MIN
#define	INTMAX_MAX		INT64_MAX
#define	UINTMAX_MAX		UINT64_MAX

/* misc. types */

/* ptrdiff_t is a signed intptr_t */
#define	PTRDIFF_MIN		INTPTR_MIN
#define	PTRDIFF_MAX		INTPTR_MAX

/* sig_atomic_t is an int */
#define	SIG_ATOMIC_MIN		INT32_MIN
#define	SIG_ATOMIC_MAX		INT32_MAX

#ifndef SIZE_MAX
/* size_t is the same as an uintptr_t */
#define	SIZE_MAX		UINTPTR_MAX
#endif
#ifndef SSIZE_MAX
/* ssize_t is the same as an intptr_t */
#define	SSIZE_MAX		INTPTR_MAX
#endif

/* C11 optional */
#if !defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__)
#define RSIZE_MAX		(SIZE_MAX >> 1)
#endif /* __STDC_WANT_LIB_EXT1__ */

/* wchar_t is an unsigned short */
#define	WCHAR_MIN		0U
#define	WCHAR_MAX		0xFFFDU		/* match <wchar.h> */
#define	WINT_MIN		0U
#define	WINT_MAX		0xFFFFFFFFUL

#endif	/* ndef C++ or def __STDC_LIMIT_MACROS */


/* Apple says when to not define these */

#if (!defined(__cplusplus)) || defined(__STDC_CONSTANT_MACROS)

#define	INT8_C(x)	((int8_t)x)
#define	INT16_C(x)	((int16_t)x)
#define	INT32_C(x)	(x ## L)
#define	INT64_C(x)	(x ## LL)

#define	UINT8_C(x)	((uint8_t)x)
#define	UINT16_C(x)	((uint16_t)x)
#define	UINT32_C(x)	(x ## UL)
#define	UINT64_C(x)	(x ## ULL)

#define	INTMAX_C(x)	(x ## LL)
#define	UINTMAX_C(x)	(x ## ULL)

#endif	/* ndef C++ or def __STDC_CONSTANT_MACROS */

#endif	/* ndef _STDINT_H */
