# $MirOS$
# $OpenBSD: Makefile,v 1.3 2004/02/01 14:22:44 jmc Exp $

DIR=	papers/kernmalloc
SRCS=	kernmalloc.t appendix.t
MACROS=	-ms
EXTRA=	alloc.fig usage.tbl

paper.ps: ${SRCS} alloc.fig usage.tbl
	${SOELIM} ${SRCS} | ${TBL} | ${PIC} | ${EQN} | ${GRIND} | \
	    ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
