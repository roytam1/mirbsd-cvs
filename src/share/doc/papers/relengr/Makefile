# $MirOS$
# $OpenBSD: Makefile,v 1.3 2004/02/01 14:22:45 jmc Exp $

DIR=	papers/relengr
SRCS=	0.t 1.t 2.t 3.t
MACROS=	-ms
EXTRA=	ref.bib ref.bib.ig tmac.srefs
REFER=	refer -n -e -l -s -p ref.bib

paper.ps: ${SRCS}
	${REFER} ${SRCS} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
