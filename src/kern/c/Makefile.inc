# $MirOS: src/kern/c/Makefile.inc,v 1.5 2007/02/06 16:28:36 tg Exp $

# imports:
# ifdef(KERNSTAND)	-> bootloader, no kernel/libc only stuff
# ifdef(KERNNOGCC)	-> -fhosted -lgcc, no gcc replacement stuff
# ifdef(SMALL)		-> -DSMALL, prefer size over speed optimisation

.include "${KERNBASE}/Makefile.inc"

# md stuff must define sources for the following functions:
# htonl() htons() ntohl() ntohs()
# strlen()

.include "${KERNBASE}/c/${MACHINE_ARCH}/Makefile.inc"

.PATH: ${KERNBASE}/c/${MACHINE_ARCH}
.PATH: ${KERNBASE}/c

# SRCS, UNIFDEF_SRCS: kernel, userland, bootloader
# KUSRCS, UIF_KUSRCS: kernel, userland

UIF_KUSRCS+=	wcslen.c strlen.c -DWIDEC

# …

.ifndef KERNSTAND
SRCS+=		${KUSRCS}
UNIFDEF_SRCS+=	${UIF_KUSRCS}
.endif

.for _z _q _s in ${UNIFDEF_SRCS}
SRCS+=		${_z}
CLEANFILES+=	${_z}

${_z}: ${_q}
	-unifdef ${_s:S/,/ /g} $> >$@

beforedepend: ${_z}
.endfor
