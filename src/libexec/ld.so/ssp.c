/*-
 * Copyright (c) 2008
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
 */

#include <sys/param.h>
#include <sys/sysctl.h>
#include "archdep.h"

__RCSID("$MirOS$");

#if (defined(__SSP__) || defined(__SSP_ALL__)) && \
    !defined(__IN_MKDEP) && !defined(lint)
#error "You must compile this file with -fno-stack-protector -fno-stack-protector-all"
#endif

extern long __guard[8];

void __guard_setup(void);

void
__guard_setup(void)
{
	unsigned char *cp;
	size_t n;
	int mib[2];

	cp = (unsigned char *)__guard;

	*cp++ = 0;
	*cp++ = 0;
	*cp++ = '\n';
	*cp++ = 255;

	n = sizeof (__guard) - 4;
	mib[0] = CTL_KERN;
	mib[1] = KERN_ARND;
	/* _dl_sysctl is implemented in asm and thusly safe to use */
	_dl_sysctl(mib, 2, cp, &n, NULL, 0);
}
