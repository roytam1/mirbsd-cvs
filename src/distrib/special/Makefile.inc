# $MirOS: src/distrib/special/Makefile.inc,v 1.2 2006/02/14 20:47:53 tg Exp $

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
