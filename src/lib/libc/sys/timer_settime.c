/*	$OpenBSD: timer_settime.c,v 1.6 2005/08/08 08:05:38 espie Exp $ */

#include <signal.h>
#include <time.h>
#include <errno.h>

__RCSID("$MirOS$");

struct itimerspec;

int timer_settime(timer_t, int, const struct itimerspec *,
    struct itimerspec *);

/* ARGSUSED */
int
timer_settime(timer_t timerid __unused, int flags __unused,
    const struct itimerspec *value __unused,
    struct itimerspec *ovalue __unused)
{
	errno = ENOSYS;
	return -1;
}
