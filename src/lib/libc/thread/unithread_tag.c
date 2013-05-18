/* $OpenBSD: unithread_tag.c,v 1.1 2004/06/07 21:11:23 marc Exp $ */

/* PUBLIC DOMAIN: No Rights Reserved. Marco S Hyman <marc@snafu.org> */

#include <sys/time.h>
#include "thread_private.h"

__RCSID("$MirOS$");

WEAK_PROTOTYPE(_thread_tag_lock);
WEAK_PROTOTYPE(_thread_tag_unlock);
WEAK_PROTOTYPE(_thread_tag_storage);

WEAK_ALIAS(_thread_tag_lock);
WEAK_ALIAS(_thread_tag_unlock);
WEAK_ALIAS(_thread_tag_storage);

void
WEAK_NAME(_thread_tag_lock)(void **tag __unused)
{
	return;
}

void
WEAK_NAME(_thread_tag_unlock)(void **tag __unused)
{
	return;
}

void   *
WEAK_NAME(_thread_tag_storage)(void **tag __unused, void *init,
    size_t initsz __unused, void *err __unused)
{
	return init;
}
