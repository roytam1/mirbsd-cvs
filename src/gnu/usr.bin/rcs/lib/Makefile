# $MirOS: src/gnu/usr.bin/rcs/lib/Makefile,v 1.1.7.1 2005/03/06 17:00:10 tg Exp $

LIB=	rcs
NOPIC=	yes
SRCS=	getdate.c merger.c rcsedit.c rcsfcmp.c rcsfnms.c rcsgen.c \
	rcskeep.c rcskeys.c rcslex.c rcsmap.c rcsrev.c rcssyn.c \
	rcstime.c rcsutil.c version.c

install:

CVSLIB=	${.CURDIR}/../../cvs/lib
.PATH: ${CVSLIB}

CPPFLAGS+=	-I${CVSLIB}

.include <bsd.lib.mk>
