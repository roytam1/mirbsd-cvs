# $MirOS$
# $OpenBSD: Makefile,v 1.2 2004/02/01 15:18:01 jmc Exp $

DIR=	usd/05.dc
SRCS=	dc
MACROS=	-ms

paper.ps: ${SRCS}
	${EQN} ${SRCS} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
