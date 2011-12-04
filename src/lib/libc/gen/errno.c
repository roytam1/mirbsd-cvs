#include <sys/cdefs.h>
__RCSID("$MirOS$");

/* PUBLIC DOMAIN: No Rights Reserved.   Marco S Hyman <marc@snafu.org> */

#if 0
static char rcsid[] = "$OpenBSD: errno.c,v 1.4 2004/07/17 20:38:43 marc Exp $";
#endif /* LIBC_SCCS and not lint */

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
