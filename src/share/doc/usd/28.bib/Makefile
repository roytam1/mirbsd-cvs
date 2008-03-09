# $MirOS: src/share/doc/usd/28.bib/Makefile,v 1.1.7.1 2005/03/06 16:17:49 tg Exp $
# @(#)Makefile	6.2 (Berkeley) 6/30/90

DIR=	usd/28.bib
SRCS=	bibdoc.ms
MACROS=	-msU

paper.ps: ${SRCS}
	${BIB} ${SRCS} | ${TBL} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
