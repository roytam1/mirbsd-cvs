# $MirOS$
# @(#)Makefile	6.3 (Berkeley) 4/17/91

# refer.mac should be typed on a 12 pitch Daisy wheel printer
DIR=	usd/26.refer
SRCS=	refer.bib
MACROS=	-msU
REFER=	refer -p biblio
EXTRA=	biblio mx.doc refer.mac
CLEANFILES=biblio.ig

paper.ps: ${SRCS}
	${REFER} ${SRCS} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
