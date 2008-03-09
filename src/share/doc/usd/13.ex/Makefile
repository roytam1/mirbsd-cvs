# $MirOS$
# @(#)Makefile	6.2 (Berkeley) 6/30/90

DIR=	usd/13.ex
SRCS=	ex.rm
MACROS=	-msU
EXTRA=	ex.summary
CLEANFILES=summary.*

paper.ps: ${SRCS} summary.${PRINTER}
	${ROFF} ${SRCS} >${.TARGET}

summary.${PRINTER}: ex.summary
	${TBL} ex.summary | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
