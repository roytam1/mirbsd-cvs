# $MirOS: src/lib/libmbfun/Makefile,v 1.1 2010/08/14 20:53:05 tg Exp $

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

.for _z _q _s in ${UNIFDEF_SRCS} ${UIF_LSRCS}
CLEANFILES+=	${_z}

${_z}: ${_q}
	-unifdef ${_s:S/,/ /g} $> >$@

beforedepend: ${_z}
.endfor

.include <bsd.lib.mk>
