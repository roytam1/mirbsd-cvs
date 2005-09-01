# $MirOS: ports/infrastructure/mk/mirports.bsd.mk,v 1.2 2005/06/17 20:20:03 tg Exp $
#-
# This file replaces <bsd.own.mk> as EXTRA_SYS_MK_INCLUDES
# during MirPorts builds.

.ifndef _MIRPORTS_BSD_MK
_MIRPORTS_BSD_MK=1

# First, get the defaults.
.include <bsd.own.mk>

# Second, override where necessary.
DEBUGLIBS=		No

BINDIR=			${PREFIX}/bin
LIBDIR=			${PREFIX}/lib
MANDIR=			${PREFIX}/man/cat
SHAREDIR=		${PREFIX}/share

.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=		${TRUEPREFIX}
.endif
BSD_PREFIX=		${PREFIX}

.endif
