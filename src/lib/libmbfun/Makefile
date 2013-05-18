# $MirOS: src/lib/libmbfun/Makefile,v 1.2 2010/08/14 21:10:18 tg Exp $

LIB=		mbfun
HDRS=		mbfun.h

FUNCTIONS+=	cdblockedread

.for _f in ${FUNCTIONS}
SRCS+=		${_f}.c
MAN+=		${_f}.3
.endfor

.for _src _dst in ${UIF_FUNCS}
UNIFDEF_SRCS+=	${_src}.c ${_dst}.c -DL_${_dst}
MLINKS+=	${_src}.3 ${_dst}.3
.endfor

KERNNOGCC=		#defined
KERNPICKSRCS=		Yes
KERNBASE?=		${.CURDIR}/../../kern
.include "${KERNBASE}/c/Makefile.inc"
SRCS+=			${KXSRCS}
UNIFDEF_SRCS+=		${UIF_KXSRCS}

.for _z _q _s in ${UNIFDEF_SRCS}
CLEANFILES+=	${_z}

${_z}: ${_q}
	-unifdef ${_s:S/,/ /g} $> >$@

beforedepend: ${_z}
.endfor

.include <bsd.lib.mk>
