# $MirOS$
# @(#)Makefile	6.2 (Berkeley) 6/30/90

DIR=	psd/11.adb
SRCS=	adb.ms
MACROS=	-ms

paper.ps: ${SRCS}
	${EQN} ${SRCS} | ${TBL} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
