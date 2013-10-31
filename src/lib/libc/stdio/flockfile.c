/*	$OpenBSD: flockfile.c,v 1.7 2004/09/28 18:12:44 otto Exp $	*/

#include <sys/time.h>
#include <stdio.h>
#include "thread_private.h"

__RCSID("$MirOS$");

/*
 * Subroutine versions of the macros in <stdio.h>
 * Note that these are all no-ops because libc does not do threads.
 * Strong implementation of file locking in libc_r/uthread/uthread_file.c
 */

#undef flockfile
#undef ftrylockfile
#undef funlockfile

WEAK_PROTOTYPE(flockfile);
WEAK_PROTOTYPE(ftrylockfile);
WEAK_PROTOTYPE(funlockfile);

WEAK_ALIAS(flockfile);
WEAK_ALIAS(ftrylockfile);
WEAK_ALIAS(funlockfile);

void
WEAK_NAME(flockfile)(FILE * fp __attribute__((__unused__)))
{
}


int
WEAK_NAME(ftrylockfile)(FILE *fp __attribute__((__unused__)))
{

	return 0;
}

void
WEAK_NAME(funlockfile)(FILE * fp __attribute__((__unused__)))
{
}
