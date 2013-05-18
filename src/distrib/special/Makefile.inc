# $MirOS: src/distrib/special/Makefile.inc,v 1.4 2006/05/26 19:01:18 tg Exp $

.ifndef _MODSRC_DISTRIB_SPECIAL_MAKEFILE_INC
_MODSRC_DISTRIB_SPECIAL_MAKEFILE_INC=1

.include <bsd.own.mk>

CPPFLAGS+=	-D_USE_OLD_CURSES_
COPTS+=		-Os
NOMAN=		yes
LDSTATIC=	# empty

.if defined(SRC_PATH)
.PATH: ${SRC_PATH}
CPPFLAGS+=	-isystem ${SRC_PATH}
.endif

.endif
