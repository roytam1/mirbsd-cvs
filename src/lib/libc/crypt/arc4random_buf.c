/*-
 * Copyright (c) 2010
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 *-
 * Implement a useful arc4random(3) related API.
 */

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "arc4random.h"
#include "thread_private.h"

__RCSID("$MirOS: src/lib/libc/crypt/arc4random_buf.c,v 1.1 2010/09/12 17:10:53 tg Exp $");

void
arc4random_buf(void *buf_, size_t len)
{
	uint8_t *buf = (uint8_t *)buf_;
	pid_t mypid = 0;

	if (!len)
		return;

	_ARC4_LOCK();

	/* reinitialise if necessary */
	if (!a4state.a4s_initialised ||
	    (a4state.a4s_stir_pid != (mypid = getpid())))
		arc4random_stir_locked(mypid);

	/* randomly skip 1-4 bytes */
	/*XXX this should be constant-time */
	buf[0] = arcfour_byte(&a4state.cipher) & 3;
	while (buf[0]--)
		(void)arcfour_byte(&a4state.cipher);

	/* fill the buffer */
	while (len--) {
		if (--a4state.a4s_count <= 0)
			arc4random_stir_locked(mypid);
		buf[len] = arcfour_byte(&a4state.cipher);
	}

	_ARC4_UNLOCK();
}
