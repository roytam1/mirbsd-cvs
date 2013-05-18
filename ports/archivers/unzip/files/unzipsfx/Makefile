# $MirOS$

PROG=		unzipsfx
SRCS=		crypt.c extract.c fileio.c globals.c inflate.c \
		match.c process.c ttyio.c unix.c unzip.c
CPPFLAGS+=	-DSFX
# this shouldn't really be necessary…
#LDSTATIC=	-static

.include <bsd.prog.mk>
