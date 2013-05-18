# $MirOS: src/share/doc/usd/Makefile,v 1.2 2005/03/06 19:38:32 tg Exp $
# $OpenBSD: Makefile,v 1.8 2004/10/10 02:53:28 mickey Exp $

INSTDIR=usd
FILES=	00.contents Makefile Title
SUBDIR!=echo */Makefile | sed 's,/Makefile[[:>:]],,g'

.include <bsd.own.mk>

all: _SUBDIRUSE
all: Title.txt contents.txt

Title.ps: ${FILES}
	${ROFF} Title >${.TARGET}
Title.txt: ${FILES}
	${NROFF} Title >${.TARGET}

contents.ps: ${FILES}
	${ROFF} -ms 00.contents >${.TARGET}
contents.txt: ${FILES}
	${NROFF} -ms 00.contents >${.TARGET}

beforeinstall:
	install -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} ${FILES} \
	    ${DESTDIR}${DOCDIR}/${INSTDIR}

.include <bsd.subdir.mk>
