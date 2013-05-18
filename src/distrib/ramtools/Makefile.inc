# $MirOS: src/distrib/ramtools/Makefile.inc,v 1.1 2006/05/15 19:20:16 tg Exp $

.ifndef _MODSRC_DISTRIB_SPECIAL_MAKEFILE_INC
_MODSRC_DISTRIB_SPECIAL_MAKEFILE_INC=1

.include <bsd.own.mk>

COPTS+=		-Os
NOMAN=		yes

.if defined(SRC_PATH)
.PATH: ${SRC_PATH}
CPPFLAGS+=	-isystem ${SRC_PATH}
.endif

.endif
