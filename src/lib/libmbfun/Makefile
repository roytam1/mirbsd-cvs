# $MirOS: src/lib/libmbfun/Makefile,v 1.4 2014/02/19 16:59:32 tg Exp $

LIB=		mbfun
HDRS=		mbfun.h

FUNCTIONS+=	ambstowcs
FUNCTIONS+=	cdblockedread

SRCS+=		awcstombs.c
SRCS+=		optu8to16vis.c

UIF_FUNCS+=	ambstowcs ambsntowcs
UIF_FUNCS+=	awcstombs awcsntombs

UNIFDEF_SRCS+=	mbsnrtowcsvis.c mbsrtowcs.c -DMBSNRTOWCSVIS

MLINKS+=	ambstowcs.3 awcstombs.3

.for _f in ${FUNCTIONS}
SRCS+=		${_f}.c
MAN+=		${_f}.3
.endfor

.for _src _dst in ${UIF_FUNCS}
UNIFDEF_SRCS+=	${_dst}.c ${_src}.c -DL_${_dst}
MLINKS+=	${_src}.3 ${_dst}.3
.endfor

KERNNOGCC=		#defined
KERNPICKSRCS=		Yes
KERNBASE?=		${.CURDIR}/../../kern
.include "${KERNBASE}/c/Makefile.inc"
SRCS+=			${KXSRCS}
UNIFDEF_SRCS+=		${UIF_KXSRCS}

LIBCSRCDIR?=${.CURDIR}/../libc
.PATH: ${LIBCSRCDIR}/i18n

.for _z _q _s in ${UNIFDEF_SRCS}
CLEANFILES+=	${_z}

${_z}: ${_q}
	-unifdef ${_s:S/,/ /g} $> >$@

beforedepend: ${_z}
.endfor

.include <bsd.lib.mk>
