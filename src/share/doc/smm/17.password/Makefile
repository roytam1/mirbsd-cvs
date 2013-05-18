# $MirOS$
# @(#)Makefile	6.2 (Berkeley) 6/30/90

DIR=	smm/17.password
SRCS=	password.ms
MACROS=	-msU

paper.ps: ${SRCS}
	${TBL} ${SRCS} | ${EQN} | ${ROFF} >${.TARGET}

.include <bsd.doc.mk>
