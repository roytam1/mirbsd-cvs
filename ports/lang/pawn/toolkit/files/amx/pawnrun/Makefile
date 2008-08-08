# $MirOS$

PROG=		pawnrun
SRCS+=		pawnrun.c amx.c amxcore.c amxdbg.c
CPPFLAGS+=	-DAMXDBG

DPADD+=		${LIBDL}
LDADD+=		-ldl

NEED_AMXCONS=	Yes

.include <bsd.prog.mk>
