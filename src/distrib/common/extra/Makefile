# $MirOS: src/distrib/common/extra/Makefile,v 1.1 2006/08/17 14:17:47 tg Exp $

TOPDIR=		${.CURDIR}/../..

.if ${MACHINE} == "i386"
MACHCONF=	i386-big	# bsd.rd, ISO image
.else
.  error machine not supported
.endif

.include "../Makefile"
