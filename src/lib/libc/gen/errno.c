/*	$OpenBSD: errno.c,v 1.5 2005/08/08 08:05:34 espie Exp $ */
/* PUBLIC DOMAIN: No Rights Reserved.   Marco S Hyman <marc@snafu.org> */

#include <sys/cdefs.h>
__RCSID("$MirOS: src/lib/libc/gen/errno.c,v 1.2 2005/03/06 20:28:40 tg Exp $");

#include <errno.h>
#undef errno

/*
 * global errno for unthreaded programs.
 */
int errno;

/*
 * weak version of function used by unthreaded programs.
 */
int *
___errno(void)
{
	return &errno;
}

__weak_alias(__errno, ___errno);
