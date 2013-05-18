# $MirOS: ports/infrastructure/mk/mirports.bsd.mk,v 1.4 2005/09/12 22:53:19 tg Exp $
#-
# This file replaces <bsd.own.mk> as EXTRA_SYS_MK_INCLUDES
# during MirPorts builds.

.ifndef _MIRPORTS_BSD_MK
_MIRPORTS_BSD_MK=1

.if defined(TRUEPREFIX) && !empty(TRUEPREFIX)
BSD_PREFIX=		${TRUEPREFIX}
.elif defined(PREFIX) && !empty(PREFIX)
BSD_PREFIX=		${PREFIX}
.endif

BINDIR?=		${BSD_PREFIX}/bin

.include <bsd.own.mk>

# Override where necessary.

.endif
