#if 0
# $MirOS: src/share/misc/licence.template,v 1.24 2008/04/22 11:43:31 tg Rel $
#-
# Copyright (c) 2008
#	Thorsten „mirabilos“ Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# is granted to deal in this work without restriction, including un
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.

.include <bsd.own.mk>

PREFIX?=	/usr/mpkg
CPPFLAGS+=	-I${PREFIX:Q}/include
PROG=		asctopng
NOMAN=		Yes
LDADD+=		-L${PREFIX:Q}/lib -lgd -lpng -ljpeg -lz -lm
LDSTATIC=	-static

.include <bsd.prog.mk>

.if "0" == "1"
#endif

#include <sys/param.h>
#include <err.h>
#include <wchar.h>
#include "gd.h"

__RCSID("$MirOS$");

/* XFree86® fixed-misc 9x18 */
static char gdfixedmiscData[] = {
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,0,0,1,0,0,
0,0,0,1,0,0,1,0,0,
0,0,0,1,0,0,1,0,0,
0,0,0,1,0,0,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,0,0,1,0,0,0,
0,0,1,0,0,1,0,0,0,
0,0,1,0,0,1,0,0,0,
1,1,1,1,1,1,1,1,0,
0,0,1,0,0,1,0,0,0,
0,0,1,0,0,1,0,0,0,
1,1,1,1,1,1,1,1,0,
0,0,1,0,0,1,0,0,0,
0,0,1,0,0,1,0,0,0,
0,0,1,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,0,0,
0,0,1,0,1,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,0,0,1,0,1,0,0,
0,0,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,0,0,0,0,1,0,
0,1,0,1,0,0,1,0,0,
0,1,0,1,0,0,1,0,0,
0,0,1,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,1,0,0,
0,0,1,0,0,1,0,1,0,
0,0,1,0,0,1,0,1,0,
0,1,0,0,0,0,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,0,0,
0,1,0,0,1,0,0,0,0,
0,1,0,0,1,0,0,0,0,
0,1,0,0,1,0,0,0,0,
0,0,1,1,0,0,0,0,0,
0,0,1,1,0,0,0,1,0,
0,1,0,0,1,0,1,0,0,
0,1,0,0,0,1,0,0,0,
0,1,0,0,1,0,1,0,0,
0,0,1,1,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,1,0,0,1,0,0,1,0,
0,0,1,0,1,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,1,0,1,0,0,
0,1,0,0,1,0,0,1,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,1,0,1,0,
0,1,0,0,0,1,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,1,0,0,0,1,0,
0,1,0,1,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,1,0,0,0,0,
0,0,1,0,1,0,0,0,0,
0,1,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,0,1,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,1,0,0,
0,0,0,0,1,0,1,0,0,
0,0,0,1,0,0,1,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,1,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,0,1,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,1,0,0,
0,0,1,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,1,1,1,0,0,0,
0,1,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,1,0,
0,0,0,1,1,1,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,1,0,0,
0,0,1,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,1,1,0,1,0,
0,1,0,1,0,1,0,1,0,
0,1,0,1,0,1,0,1,0,
0,1,0,1,0,1,0,1,0,
0,1,0,1,0,1,0,1,0,
0,1,0,0,1,1,1,0,0,
0,0,1,0,0,0,0,0,0,
0,0,0,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,0,1,1,1,1,1,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,1,1,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,1,0,0,
0,0,1,0,0,0,0,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,1,0,0,0,0,1,0,
0,0,0,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,1,1,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,1,1,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,1,1,1,1,1,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,1,1,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,1,0,0,0,1,0,0,0,
0,1,0,0,0,1,0,0,0,
0,0,1,1,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,1,0,0,0,
0,1,0,0,1,0,0,0,0,
0,1,0,1,0,0,0,0,0,
0,1,1,0,1,0,0,0,0,
0,1,0,0,0,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,1,0,0,0,1,1,0,
0,1,0,1,0,1,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,1,0,0,0,0,1,0,
0,1,0,1,0,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,0,1,0,1,0,
0,1,0,0,0,0,1,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,1,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,1,0,
0,0,0,0,0,0,0,0,1,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,0,0,
0,1,1,1,1,1,0,0,0,
0,1,0,0,1,0,0,0,0,
0,1,0,0,0,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,1,0,0,0,1,0,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,1,0,1,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,1,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,1,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
1,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,1,0,
0,0,1,1,1,1,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,1,1,1,1,0,0,
0,1,1,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,1,0,0,0,0,1,0,
0,1,0,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,1,1,1,1,0,1,0,
0,1,0,0,0,0,1,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,1,0,
0,0,1,1,1,1,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,1,1,1,1,1,1,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,1,0,0,
0,0,0,1,0,0,0,1,0,
0,0,0,1,0,0,0,1,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,1,1,1,1,1,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,0,1,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,1,0,0,
0,0,1,1,1,1,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,1,1,1,1,0,0,
0,1,1,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,1,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,0,1,0,0,
0,0,1,0,0,0,1,0,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,1,1,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,1,0,0,0,
0,1,0,0,1,0,0,0,0,
0,1,0,1,1,0,0,0,0,
0,1,1,0,0,1,0,0,0,
0,1,0,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,0,1,1,0,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,1,1,1,1,0,0,
0,1,1,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,1,1,1,0,0,0,
0,1,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,1,0,0,0,1,0,0,
0,1,0,1,1,1,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,1,1,0,1,0,
0,0,1,0,0,0,1,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,1,0,
0,0,0,1,1,1,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,1,1,1,0,0,
0,0,1,1,0,0,0,1,0,
0,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,0,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,1,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,1,1,1,1,1,1,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,0,1,0,0,0,1,0,
0,0,0,0,1,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,1,1,0,
0,0,1,1,1,1,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,0,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,1,0,1,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,0,0,0,0,0,1,0,
0,0,1,0,0,0,1,0,0,
0,0,0,1,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,1,0,0,0,
0,0,1,0,0,0,1,0,0,
0,1,0,0,0,0,0,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,0,0,0,0,1,0,
0,0,1,0,0,0,0,1,0,
0,0,0,1,0,0,1,0,0,
0,0,0,1,0,0,1,0,0,
0,0,0,1,0,0,1,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,1,0,0,1,0,0,0,0,
0,0,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,1,0,0,
0,0,0,0,0,1,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,1,0,0,0,0,0,
0,0,1,0,0,0,0,0,0,
0,1,1,1,1,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,1,1,1,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,1,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,1,1,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,1,1,1,0,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,0,1,1,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,0,0,0,1,0,0,0,0,
0,1,1,1,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,

0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,1,1,0,0,0,1,0,
0,1,0,0,1,0,0,1,0,
0,1,0,0,0,1,1,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0
};

static gdFont gdfixedmiscRep = {
	95,
	32,
	9,
	18,
	gdfixedmiscData
};

int
main(int argc, char *argv[])
{
	gdImagePtr im;
	size_t n = 0;
	int i, black, white;

	if (argc-- < 2)
		errx(1, "syntax: %s string […]", argv[0]);
	++argv;

	for (i = 0; i < argc; ++i)
		n = MAX(n, strlen(argv[i]));

	im = gdImageCreate(n * 9, 18 * argc);
	white = gdImageColorAllocate(im, 255, 255, 255);
	black = gdImageColorAllocate(im, 0, 0, 0);
	gdImageColorTransparent(im, white);

	for (i = 0; i < argc; ++i)
		gdImageString(im, &gdfixedmiscRep, 0, 18 * i, argv[i], black);

	gdImagePng(im, stdout);
	return (0);
}

#if 0
.endif
#endif