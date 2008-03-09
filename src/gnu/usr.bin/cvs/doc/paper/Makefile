# $MirOS$

DIR=	papers/cvs-paper
SRCS=	cvs-paper.ms
MACROS=	-ms

.if !exists(cvs-paper.ms) && exists(${.CURDIR}/../cvs-paper.ms)
FILES=	${.CURDIR}/../cvs-paper.ms
.endif

paper.ps: ${SRCS}
	${SOELIM} ${SRCS} | ${PIC} | ${TBL} | ${ROFF} >$@

.include <bsd.doc.mk>
