/*	$OpenBSD: explicit_bzero.c,v 1.1 2011/01/10 23:23:56 tedu Exp $ */
/*
 * Public domain.
 * Written by Ted Unangst
 */

#include <libckern.h>

__RCSID("$MirOS: src/kern/c/explicit_bzero.c,v 1.1 2011/07/17 17:21:02 tg Exp $");

/*
 * explicit_bzero - don't let the compiler optimize away bzero
 */
void
explicit_bzero(void *p, size_t n)
{
	/*
	 * we forward to the "correct" bzero implementation,
	 * instead of just making this a symbol alias in the
	 * arch subdirectory's copy, because e.g. the kernel
	 * on i386 (locore.S) has per-CPU optimised ones; in
	 * userspace we want to keep the symbol in libmbfun,
	 * to not clutter libc symbol space
	 */
	bzero(p, n);
}
