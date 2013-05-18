# $MirOS$

READLINE_PREFIX=	${LOCALBASE}/pkgview/libreadline
CPPFLAGS+=		-I${READLINE_PREFIX:Q}/include
LDFLAGS+=		-Wl,-rpath,${READLINE_PREFIX:Q}/lib \
			-L${READLINE_PREFIX:Q}/lib
