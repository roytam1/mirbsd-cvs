# $MirOS: src/distrib/common/extra/Makefile,v 1.3 2008/07/12 22:06:16 tg Exp $

TOPDIR=		${.CURDIR}/../..

.if ${MACHINE} == "i386"
MACHCONF=	i386-sshd	# ISO image
.else
.  error machine not supported
.endif

.include "../Makefile"
