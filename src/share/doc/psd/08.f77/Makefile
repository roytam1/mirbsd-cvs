# $MirOS$
# @(#)Makefile	5.2 (Berkeley) 6/30/90

DIR=	psd/08.f77
SRCS=	f77.ms
MACROS=	-msU

paper.ps: ${SRCS}
	${TBL} ${SRCS} | ${EQN} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
