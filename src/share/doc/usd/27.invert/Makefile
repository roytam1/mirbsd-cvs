# $MirOS$
# @(#)Makefile	5.1 (Berkeley) 6/30/90

DIR=	usd/27.invert
SRCS=	refer
MACROS=	-msU

paper.ps: ${SRCS}
	${REFER} ${SRCS} | ${TBL} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
