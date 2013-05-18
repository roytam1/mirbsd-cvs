# $MirOS: src/kern/c/Makefile.inc,v 1.6 2007/02/06 18:58:06 tg Exp $

.ifndef _KERNBASE_C_MAKEFILE_INC
_KERNBASE_C_MAKEFILE_INC=	#defined

# imports:
# ifdef(KERNSTAND)	-> bootloader, no kernel/libc only stuff
# ifdef(KERNNOGCC)	-> -fhosted -lgcc, no gcc replacement stuff
# ifdef(SMALL)		-> -DSMALL, prefer size over speed optimisation

.include "${KERNBASE}/Makefile.inc"

# md stuff must define sources for the following functions:
# htonl() htons() ntohl() ntohs()
# strlen() wcslen()

.include "${KERNBASE}/c/${MACHINE_ARCH}/Makefile.inc"

.PATH: ${KERNBASE}/c/${MACHINE_ARCH}
.PATH: ${KERNBASE}/c

# SRCS, UNIFDEF_SRCS:	kernel, userland, bootloader
# KUSRCS, UIF_KUSRCS:	kernel, userland
# LSRCS, UIF_LSRCS:	lint libraries (userland)

# …

.ifndef KERNSTAND
SRCS+=		${KUSRCS}
UNIFDEF_SRCS+=	${UIF_KUSRCS}
.endif

.for _z _q _s in ${UNIFDEF_SRCS}
SRCS+=		${_z}
.endfor
.for _z _q _s in ${UIF_LSRCS}
LSRCS+=		${_z}
.endfor
.for _z _q _s in ${UNIFDEF_SRCS} ${UIF_LSRCS}
CLEANFILES+=	${_z}

${_z}: ${_q}
	-unifdef ${_s:S/,/ /g} $> >$@

beforedepend: ${_z}
.endfor

.endif
