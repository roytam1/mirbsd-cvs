# $MirOS$
# @(#)Makefile	6.3 (Berkeley) 6/30/90

DIR=	psd/02.implement
SRCS=	implement
MACROS=	-msU
EXTRA=	fig1.pic fig2.pic

#XXX
REFER?=	cat
REFER?=	refer -e

paper.ps: ${SRCS} fig1.pic fig2.pic
	${SOELIM} ${SRCS} | ${REFER} | ${PIC} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
