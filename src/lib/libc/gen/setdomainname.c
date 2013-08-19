/* $MirOS: src/lib/libc/gen/setdomainname.c,v 1.6 2006/11/01 20:01:18 tg Exp $ */

/*-
 * Copyright (c) 2005
 *	Thorsten "mirabilos" Glaser <tg@mirbsd.org>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#include <sys/param.h>
#include <sys/sysctl.h>
#include <unistd.h>

__RCSID("$MirOS: src/lib/libc/gen/setdomainname.c,v 1.6 2006/11/01 20:01:18 tg Exp $");

int
setdomainname(const char *name __attribute__((unused)),
    size_t namelen __attribute__((unused)))
{
	return (0);
}