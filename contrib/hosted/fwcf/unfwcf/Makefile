# $MirOS$

PROG=		unfwcf
NOMAN=		yes
SRCS=		unfwcf.c
SRCS+=		compress.c #...
SRCS+=		c_none.c
SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

DPADD+=		${LIBZ}
LDADD+=		-lz

.include <bsd.prog.mk>
