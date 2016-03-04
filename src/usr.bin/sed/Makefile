# $MirOS: src/usr.bin/sed/Makefile,v 1.2 2005/03/13 18:33:27 tg Exp $
# $OpenBSD: Makefile,v 1.4 2010/01/04 17:50:39 deraadt Exp $

PROG=	sed
SRCS=	compile.c main.c misc.c process.c

# These get installed verbatim
.if make(install)
SUBDIR+= USD.doc
.endif

.include <bsd.prog.mk>
