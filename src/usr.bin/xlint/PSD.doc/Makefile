# $MirOS$

DIR=	psd/22.lint
SRCS=	lint.ms
MACROS=	-ms
REFER=	refer -e -p /usr/share/dict/papers/Ind

paper.ps: ${SRCS}
	${REFER} ${SRCS} | ${ROFF} >$@

.include <bsd.doc.mk>
