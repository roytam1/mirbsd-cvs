# $MirOS$
# @(#)Makefile	6.2 (Berkeley) 6/30/90

DIR=	smm/15.uucpnet
SRCS=	network.ms
MACROS=	-msU
REFER=	refer -p /usr/share/dict/papers/Ind

paper.ps: ${SRCS}
	${REFER} -e ${SRCS} | ${TBL} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
