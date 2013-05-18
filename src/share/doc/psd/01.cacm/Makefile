# $MirOS$
# @(#)Makefile	6.3 (Berkeley) 6/30/90

DIR=	psd/01.cacm
SRCS=	p.mac p1 p2 p3 p4 p5 p6
MACROS=	-msU

#XXX
REFER?=	cat
REFER?=	refer -e

paper.ps: ${SRCS}
	${REFER} ${SRCS} | ${TBL} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
