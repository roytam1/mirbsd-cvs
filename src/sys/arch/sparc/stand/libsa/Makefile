# $MirOS: src/sys/arch/sparc/stand/libsa/Makefile,v 1.2 2005/03/06 21:27:26 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/07/13 21:03:39 marc Exp $

LIB=	sa

.PATH:	${.CURDIR}/../../../../lib/libsa

S=		${.CURDIR}/../../../..
SADIR=		${.CURDIR}/..
DIR_SA=		$S/lib/libsa
DIR_KERN=	$S/lib/libkern
CPPFLAGS+=	-I${S} -I${S}/stand/boot -I${S}/lib -I${BSDSRCDIR}/lib/libz
CPPFLAGS+=	-D__INTERNAL_LIBSA_CREAD #-DCOMPAT_UFS

# stand routines
SRCS=	alloc.c exit.c exec.c getfile.c gets.c globals.c \
	memcmp.c memcpy.c memset.c printf.c snprintf.c strerror.c strncpy.c

# io routines
SRCS+=	close.c closeall.c dev.c disklabel.c dkcksum.c fstat.c ioctl.c lseek.c \
	open.c read.c stat.c write.c cread.c

# network routines
SRCS+=	arp.c ether.c in_cksum.c net.c netif.c rpc.c

# network info services
SRCS+=	bootp.c bootparam.c rarp.c

# boot filesystems
SRCS+=	ufs.c nfs.c cd9660.c

${OBJS}:	${.CURDIR}/../Makefile.inc

NOPIC=	yes

install:

.include <bsd.lib.mk>
