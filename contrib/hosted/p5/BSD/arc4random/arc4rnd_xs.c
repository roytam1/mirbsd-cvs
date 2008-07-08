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

#include <sys/types.h>
#include <stdlib.h>

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#ifndef __RCSID
#undef __IDSTRING
#undef __IDSTRING_CONCAT
#undef __IDSTRING_EXPAND
#define __IDSTRING_CONCAT(l,p)		__LINTED__ ## l ## _ ## p
#define __IDSTRING_EXPAND(l,p)		__IDSTRING_CONCAT(l,p)
#define __IDSTRING(prefix, string)				\
	static const char __IDSTRING_EXPAND(__LINE__,prefix) []	\
	    __attribute__((used)) = "@(""#)" #prefix ": " string
#define __RCSID(x)			__IDSTRING(rcsid,x)
#endif

__RCSID("$MirOS: contrib/hosted/p5/BSD/arc4random/arc4rnd_xs.c,v 1.2 2008/07/08 01:37:31 tg Exp $");

#ifndef HAVE_ARC4RANDOM_PUSHB
#define HAVE_ARC4RANDOM_PUSHB	1
#endif

XS(XS_BSD__arc4random_arc4random_xs);
XS(XS_BSD__arc4random_arc4random_xs)
{
	dXSARGS;
	dXSTARG;
	uint32_t rv;

	if (items != 0)
		Perl_croak(aTHX_ "Usage: BSD::arc4random::arc4random_xs()");

	rv = arc4random();

	XSprePUSH;
	PUSHu((UV)rv);

	XSRETURN(1);
}

XS(XS_BSD__arc4random_arc4random_pushb_xs);
XS(XS_BSD__arc4random_arc4random_pushb_xs)
{
	dXSARGS;
	dXSTARG;
	SV *sv;
	const char *buf;
	STRLEN len;
	uint32_t rv;

	if (items != 1)
		Perl_croak(aTHX_ "Usage: BSD::arc4random::arc4random_pushb_xs(buf)");

	sv = ST(0);
	buf = SvPV(sv, len);
#if HAVE_ARC4RANDOM_PUSHB
	rv = arc4random_pushb((const void *)buf, (size_t)len);
#else
	arc4random_addrandom((const unsigned char *)buf, (int)len);
	rv = arc4random();
#endif
	XSprePUSH;
	PUSHu((UV)rv);

	XSRETURN(1);
}

XS(XS_BSD__arc4random_arc4random_pushk_xs);
XS(XS_BSD__arc4random_arc4random_pushk_xs)
{
	dXSARGS;
	dXSTARG;
	SV *sv;
	const char *buf;
	STRLEN len;
	uint32_t rv;

	if (items != 1)
		Perl_croak(aTHX_ "Usage: BSD::arc4random::arc4random_pushk_xs(buf)");

	sv = ST(0);
	buf = SvPV(sv, len);
#ifdef arc4random_pushk
	rv = arc4random_pushk((const void *)buf, (size_t)len);
#else
	arc4random_addrandom((const unsigned char *)buf, (int)len);
	rv = arc4random();
#endif
	XSprePUSH;
	PUSHu((UV)rv);

	XSRETURN(1);
}

static char file[] = __FILE__;
static char func_a4r[] = "BSD::arc4random::arc4random_xs";
static char func_a4rpb[] = "BSD::arc4random::arc4random_pushb_xs";
static char func_a4rpk[] = "BSD::arc4random::arc4random_pushk_xs";

#ifdef __cplusplus
extern "C"
#endif
XS(boot_BSD__arc4random);
XS(boot_BSD__arc4random)
{
	dXSARGS;

	XS_VERSION_BOOTCHECK;

	newXS(func_a4r, XS_BSD__arc4random_arc4random_xs, file);
	newXS(func_a4rpb, XS_BSD__arc4random_arc4random_pushb_xs, file);
	newXS(func_a4rpk, XS_BSD__arc4random_arc4random_pushk_xs, file);

	XSRETURN_YES;
}
