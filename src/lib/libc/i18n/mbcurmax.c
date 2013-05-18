/* $MirOS: src/lib/libc/i18n/mbcurmax.c,v 1.7 2006/11/01 20:01:19 tg Exp $ */

/*-
 * Copyright (c) 2005, 2006
 *	Thorsten Glaser <tg@mirbsd.de>
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

#include <sys/cdefs.h>
#include <stdbool.h>
#include <stdlib.h>

#include "mir18n.h"

__RCSID("$MirOS: src/lib/libc/i18n/mbcurmax.c,v 1.7 2006/11/01 20:01:19 tg Exp $");

#if MIR18N_C_CSET == 2
__IDSTRING(MIR18N_C_CSET, "The 'C' locale is compatible to ISO-8859-1");
#elif MIR18N_C_CSET == 1
__IDSTRING(MIR18N_C_CSET, "Historical ISO-8859-1 conversions are allowed");
#else
__IDSTRING(MIR18N_C_CSET, "The 'C' locale is ISO_646.irv:1991 conformant");
#endif

int
__mb_cur_max(void)
{
	return (__locale_is_utf8 ? ((3 * 2) - 1) : 1);
}
