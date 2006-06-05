# $MirOS: src/lib/libncurses/Makefile.inc,v 1.3 2006/06/05 02:36:31 tg Exp $

.ifndef _LIBNCURSES_MAKEFILE_INC
_LIBNCURSES_MAKEFILE_INC=1

.include <bsd.own.mk>
NCMKDIR?=	${BSDSRCDIR}/lib/libncurses
NCSRCDIR?=	${BSDSRCDIR}/lib/libncurses/src

# XXX should be defined elsewhere
AWK?=		/usr/bin/awk

CPPFLAGS+=	-D"SYSTEM_NAME=\"${OSname}${OSrev}\"" -DHAVE_CONFIG_H -I.
CPPFLAGS+=	-I${NCSRCDIR} -I${NCSRCDIR}/include -I${NCSRCDIR}/ncurses
.ifdef WIDEC
CPPFLAGS+=	-D__MIROS_BUILD_LIBNCURSESW -D_XOPEN_SOURCE_EXTENDED
.endif
CPPFLAGS+=	-DNDEBUG -DHAVE_CONFIG_H

HOSTCFLAGS?=	${CFLAGS}
HOSTLDFLAGS?=	${LDFLAGS}
HOSTCFLAGS+=	${CPPFLAGS} -I${.CURDIR}

.endif
