# $MirOS$
# $OpenBSD: Makefile,v 1.3 2004/02/01 14:22:44 jmc Exp $

DIR=	papers/kerntune
SRCS=	0.t 1.t 2.t 3.t 4.t
MACROS=	-ms
EXTRA=	fig2.pic

paper.ps: ${SRCS}
	${SOELIM} ${SRCS} | ${PIC} | ${TBL} | ${EQN} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
