# $MirOS$

PROG=		mkfwcf
NOMAN=		yes
SRCS=		mkfwcf.c
SRCS+=		fts_subs.c ft_pack.c compress.c
SRCS+=		c_none.c
SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

DPADD+=		${LIBZ}
LDADD+=		-lz

.include <bsd.prog.mk>
