# $MirOS$

TOPDIR=		${.CURDIR}/../..

.if ${MACHINE} == "i386"
MACHCONF=	i386-big	# bsd.rd, ISO image
.elif ${MACHINE} == "sparc"
MACHCONF=	sparc-mr	# miniroot, no kernel
.else
.  error machine not supported
.endif

.include "../Makefile"
