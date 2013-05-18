#if 0 /* this line is a comment in mirmake */
# @mgcc: ignore from here
#-
# $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $
#-
# Copyright © 2008, 2011
#	Thorsten “mirabilos” Glaser <tg@mirbsd.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
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
#-
# libposixtz.so: LD_PRELOAD shared object for POSIX time zone compatibility
#-
# This is actually both a .c source file and a Makefile.
# You can build the “libposixtz.so” file by issuing:
# $ make -f posixtz.c
# Pretty cool idea of mine, eh?

.include <bsd.own.mk>

LIB=		posixtz
SRCS=		posixtz.c

CPPFLAGS+=	-I${BSDSRCDIR}/lib/libc/include
CPPFLAGS+=	-I${BSDSRCDIR}/lib/libc/time

_LIBS_STATIC=	no
SHLIB_VERSION=	-
SHLIB_SONAME=	libposixtz.so
CLEANFILES+=	libposixtz.so

.include <bsd.lib.mk>

# @mirmake: ignore from here
.if "0" == "1"
# @mgcc: end ignore
#endif /* this line is a comment in mirmake */

#include <sys/param.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifndef SYSKERN_MIRTIME_H
/* MirOS #10 API */
#include <sys/taitime.h>
#endif

__RCSID("$MirOS: contrib/code/Snippets/posixtz.c,v 1.4 2008/08/08 12:34:21 tg Exp $");

#ifndef SYSKERN_MIRTIME_H
/* import libc private interface – XXX subject to change without notice! */
extern tai64_t _leaps[];
extern bool _leaps_initialised;

void switch_to_posix(void) __attribute__((constructor));

void
switch_to_posix(void)
{
	_leaps[0] = 0;
	_leaps_initialised = true;
}
#endif

#undef SKIP_LEAPSECS
#undef SKIPPED_LEAPSECS
#define SKIP_LEAPSECS 1
#include "localtime.c"
#ifndef SKIPPED_LEAPSECS
# error your ${BSDSRCDIR}/lib/libc/time/localtime.c is too old
#endif

#if 0
# @mirmake: end ignore
.endif
#endif

# /* EOF for mirmake and mgcc */
