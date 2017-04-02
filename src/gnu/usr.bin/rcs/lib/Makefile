# $MirOS: src/gnu/usr.bin/rcs/lib/Makefile,v 1.4 2005/12/06 09:49:22 tg Exp $

LIB=	rcs
NOPIC=	yes
SRCS=	getdate.c merger.c rcsedit.c rcsfcmp.c rcsfnms.c rcsgen.c \
	rcskeep.c rcskeys.c rcslex.c rcsmap.c rcsrev.c rcssyn.c \
	rcstime.c rcsutil.c version.c

install:

.include "../Makefile.inc"

CPPFLAGS+=	-I${CVSLIB}

${CVSLIB}/getdate.c:
	@: avoid running yacc on getdate.y

.include <bsd.lib.mk>
.PATH.c: ${CVSLIB}
