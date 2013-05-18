# $MirOS$
# $OpenBSD: Makefile,v 1.3 2004/02/01 14:22:45 jmc Exp $

DIR=	papers/nqnfs
SRCS=	nqnfs.me
MACROS=	-me

paper.ps: ${SRCS}
	${PIC} ${SRCS} | ${TBL} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
