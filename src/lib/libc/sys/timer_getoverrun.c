/*	$OpenBSD: timer_getoverrun.c,v 1.5 2005/08/08 08:05:37 espie Exp $ */

#include <signal.h>
#include <time.h>
#include <errno.h>

__RCSID("$MirOS$");

int timer_getoverrun(timer_t);

/* ARGSUSED */
int
timer_getoverrun(timer_t timerid __unused)
{
	errno = ENOSYS;
	return -1;
}
