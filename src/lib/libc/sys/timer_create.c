/*	$OpenBSD: timer_create.c,v 1.6 2005/08/08 08:05:37 espie Exp $ */

#include <signal.h>
#include <time.h>
#include <errno.h>

__RCSID("$MirOS$");

struct sigevent;

int timer_create(clockid_t, struct sigevent *, timer_t *);

/* ARGSUSED */
int
timer_create(clockid_t clock_id __unused, struct sigevent *evp __unused,
    timer_t *timerid __unused)
{
	errno = ENOSYS;
	return -1;
}
