#if 0 /* this line is a comment in mirmake */
# @mgcc: ignore from here
#-
# $MirOS: contrib/code/Snippets/posixtz.c,v 1.1 2008/04/05 21:26:17 tg Exp $
#-
# Copyright (c) 2008
#	Thorsten “mirabilos” Glaser <tg@mirbsd.de>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# Advertising materials mentioning features or use of this work must
# display the following acknowledgement:
#	This product includes material provided by Thorsten Glaser.
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
SHLIB_SONAME=	libposixtz.so
CLEANFILES+=	libposixtz.so

.include <bsd.lib.mk>

# @mirmake: ignore from here
.if "0" == "1"
# @mgcc: end ignore
#endif /* this line is a comment in mirmake */

#include <sys/param.h>
#include <sys/taitime.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

__RCSID("$MirOS: contrib/code/Snippets/posixtz.c,v 1.1 2008/04/05 21:26:17 tg Exp $");

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
