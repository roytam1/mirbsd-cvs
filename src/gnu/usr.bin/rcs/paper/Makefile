# $MirOS$

DIR=	psd/13.rcs
MACROS=	-msU

.if exists(${.CURDIR}/../rcs.ms)
SRCS=	${.CURDIR}/../rcs.ms
.else
SRCS=	rcs.ms
.endif

.if exists(${.CURDIR}/../rcs_func.ms)
EXTRA=	${.CURDIR}/../rcs_func.ms
.elif exists(rcs_func.ms)
EXTRA=	rcs_func.ms
.endif

.include <bsd.doc.mk>
