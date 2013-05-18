/* $MirOS: ports/emulators/qemu/files/gnu-c99-math.h,v 1.1 2008/05/11 20:35:45 tg Exp $ */

#if (defined(__sun__) || defined(__OpenBSD__)) && defined(__GNUC__)

#include <sys/param.h>
#if (!defined(MirBSD) || (MirBSD < 0x09A6))
#define NEED_MBSD_COMPAT
#else
/* some NetBSD too, probably */
#undef NEED_MBSD_COMPAT
#endif

/*
 * C99 7.12.3 classification macros
 * and
 * C99 7.12.14 comparison macros
 *
 * ... do not work on Solaris 10 using GNU CC 3.4.x.
 * Try to workaround the missing / broken C99 math macros.
 */
#include <ieeefp.h>
#include <float.h>

#ifdef NEED_MBSD_COMPAT
#define isnormal(x)		(fabs(x) < DBL_EPSILON && !isnan(x) && !isinf(x))
#endif

#if (!defined(MirBSD) || (MirBSD < 0x0AB1))
#define	isgreater(x, y)		((x) > (y))
#define	isgreaterequal(x, y)	((x) >= (y))
#define	isless(x, y)		((x) < (y))
#define	islessequal(x, y)	((x) <= (y))

#define	isunordered(x,y)	(isnan(x) || isnan(y))
#endif

#ifdef NEED_MBSD_COMPAT
#define lrintf(x)		((long)rintf(x))
#define llrintf(x)		((long long)rintf(x))
#endif

#endif
