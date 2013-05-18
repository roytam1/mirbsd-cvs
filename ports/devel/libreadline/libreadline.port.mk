# $MirOS: ports/devel/libreadline/libreadline.port.mk,v 1.1 2008/08/19 18:07:27 tg Exp $

LIB_DEPENDS+=		pkgview/libreadline/lib/readline:readline->=5.2-3:devel/libreadline
READLINE_PREFIX=	${LOCALBASE}/pkgview/libreadline
CPPFLAGS+=		-I${READLINE_PREFIX:Q}/include
LDFLAGS+=		-Wl,-rpath,${READLINE_PREFIX:Q}/lib \
			-L${READLINE_PREFIX:Q}/lib
