# $MirOS: src/distrib/common/extra/Makefile,v 1.2 2007/08/13 19:55:10 tg Exp $

TOPDIR=		${.CURDIR}/../..

.if ${MACHINE} == "i386"
MACHCONF=	i386-big	# bsd.rd, ISO image
.elif ${MACHINE} == "sparc"
MACHCONF=	sparc-big	# bsd.rd, bsd.rd.net
.else
.  error machine not supported
.endif

.include "../Makefile"
