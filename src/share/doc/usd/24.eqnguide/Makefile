# $MirOS$
# @(#)Makefile	5.1 (Berkeley) 6/30/90

DIR=	usd/24.eqnguide
SRCS=	g.mac g0 g1 g2 g3 g4 g5
MACROS=	-msU

paper.ps: ${SRCS}
	${EQN} ${SRCS} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
