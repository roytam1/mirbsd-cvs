# $MirOS: src/usr.bin/bc/Makefile,v 1.2 2005/03/15 19:23:46 tg Exp $
# $OpenBSD: Makefile,v 1.2 2003/11/03 19:51:42 otto Exp $

PROG=		bc
SRCS=		bc.y scan.l
CPPFLAGS+=	-I.
CFLAGS+=	-Wall -Wno-unused

beforeinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${SHAREMODE} \
	    ${.CURDIR}/bc.library ${DESTDIR}/usr/share/misc/

# These get installed verbatim
.if make(install)
SUBDIR+=	USD.doc
.endif

.include <bsd.prog.mk>
