# $MirOS: src/gnu/usr.bin/rcs/lib/Makefile,v 1.2 2005/12/05 22:20:17 tg Exp $

LIB=	rcs
NOPIC=	yes
SRCS=	getdate.c merger.c rcsedit.c rcsfcmp.c rcsfnms.c rcsgen.c \
	rcskeep.c rcskeys.c rcslex.c rcsmap.c rcsrev.c rcssyn.c \
	rcstime.c rcsutil.c version.c

install:

.PATH: ${CVSLIB}
CPPFLAGS+=	-I${CVSLIB}

.include <bsd.lib.mk>
