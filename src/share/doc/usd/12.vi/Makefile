# $MirOS$
# @(#)Makefile	6.3 (Berkeley) 6/30/90

DIR=	usd/12.vi
SRCS=	vi.in vi.chars
MACROS=	-msU
EXTRA=	vi.apwh.ms vi.summary
CLEANFILES+=summary.* viapwh.*

paper.ps: ${SRCS} summary.${PRINTER} viapwh.${PRINTER}
	${ROFF} ${SRCS} >${.TARGET}

summary.${PRINTER}: vi.summary
	${TBL} vi.summary | ${ROFF} >${.TARGET}

viapwh.${PRINTER}: vi.apwh.ms
	${ROFF} vi.apwh.ms >${.TARGET}

.include <bsd.doc.mk>
