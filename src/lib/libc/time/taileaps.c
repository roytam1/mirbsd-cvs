/* $MirOS: src/lib/libc/time/tailibc.c,v 1.1 2007/02/07 20:43:24 tg Exp $ */

/*-
 * Copyright (c) 2004, 2005, 2006, 2007
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * Advertising materials mentioning features or use of this work must
 * display the following acknowledgement:
 *	This product includes material provided by Thorsten Glaser.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 */

#include <sys/param.h>
#include <sys/taitime.h>
#include <stdbool.h>
#include <stdint.h>
#include "private.h"
#include "tzfile.h"

__RCSID("$MirOS: src/lib/libc/time/tailibc.c,v 1.1 2007/02/07 20:43:24 tg Exp $");

/* private interface */
tai64_t _leaps[TZ_MAX_LEAPS + 1];
bool _leaps_initialised = false;
void _pushleap(time_t);
extern void _initialise_leaps(void);

tai64_t *
tai_leaps(void)
{
	if (__predict_false(!_leaps_initialised)) {
		_leaps[0] = 0;
		_leaps_initialised = true;
		_initialise_leaps();
		if (__predict_false(!_leaps_initialised))
			/* so we have a sanely usable result */
			_leaps[0] = 0;
	}
	return (_leaps);
}

/* private interface */
void
_pushleap(time_t leap)
{
	tai64_t *t = _leaps;

	while (__predict_true(*t))
		++t;
	*t++ = timet2tai(leap);
	*t = 0;
}
