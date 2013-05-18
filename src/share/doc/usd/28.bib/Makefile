# $MirOS$
# @(#)Makefile	6.2 (Berkeley) 6/30/90

DIR=	usd/28.bib
SRCS=	bibdoc.ms
MACROS=	-msU

paper.ps: ${SRCS}
	${BIB} ${SRCS} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
