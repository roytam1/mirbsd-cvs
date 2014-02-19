# $MirOS: src/lib/libmbfun/Makefile,v 1.3 2011/07/17 17:19:25 tg Exp $

LIB=		mbfun
HDRS=		mbfun.h

FUNCTIONS+=	ambstowcs
FUNCTIONS+=	cdblockedread

SRCS+=		awcstombs.c
SRCS+=		optu8to16vis.c

UIF_FUNCS+=	ambstowcs ambsntowcs
UIF_FUNCS+=	awcstombs awcsntombs

UNIFDEF_SRCS+=	mbsrtowcs.c mbsnrtowcsvis.c -DMBSNRTOWCSVIS

MLINKS+=	ambstowcs.3 awcstombs.3

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

LIBCSRCDIR?=${.CURDIR}/../libc
.PATH: ${LIBCSRCDIR}/i18n

.include <bsd.lib.mk>
