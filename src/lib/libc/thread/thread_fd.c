/*	$OpenBSD: thread_fd.c,v 1.8 2004/06/07 21:11:23 marc Exp $	*/

#include <sys/time.h>
#include "thread_private.h"

__RCSID("$MirOS$");

WEAK_PROTOTYPE(_thread_fd_lock);
WEAK_PROTOTYPE(_thread_fd_unlock);

WEAK_ALIAS(_thread_fd_lock);
WEAK_ALIAS(_thread_fd_unlock);

int     
WEAK_NAME(_thread_fd_lock)(int fd __unused, int lock_type __unused,
    struct timespec *timeout __unused)
{
	return 0;
}

void
WEAK_NAME(_thread_fd_unlock)(int fd __unused, int lock_type __unused)
{
}

