# $MirOS: src/distrib/ramtools/Makefile.inc,v 1.3 2006/05/26 19:01:17 tg Exp $

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
