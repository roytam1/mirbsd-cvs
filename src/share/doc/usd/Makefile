# $MirOS$
# $OpenBSD: Makefile,v 1.6 2004/04/09 12:10:04 jmc Exp $

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
