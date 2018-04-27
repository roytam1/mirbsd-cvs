# $MirOS: src/sys/arch/sparc/stand/libsa/Makefile,v 1.13 2013/08/06 17:06:26 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/07/13 21:03:39 marc Exp $

.include "${.CURDIR}/../Makefile.inc"

LIB=	sa

.PATH:	${.CURDIR}/../../../../lib/libsa
.PATH:	${.CURDIR}/../../../../lib/libkern
.PATH:	${.CURDIR}/../../../../lib/libkern/arch/sparc

S=		${.CURDIR}/../../../..
SADIR=		${.CURDIR}/..
DIR_SA=		$S/lib/libsa
DIR_KERN=	$S/lib/libkern
CPPFLAGS+=	-I$S/stand/boot -I$S/lib/libsa
CPPFLAGS+=	-D__INTERNAL_LIBSA_CREAD #-DCOMPAT_UFS
DEBUGLIBS=	No
KERNSTAND=	#defined
SMALL=		#defined

.include "${KERNBASE}/c/Makefile.inc"
.include "${KERNBASE}/z/Makefile.adler32"
.include "${KERNBASE}/z/Makefile.inc"

# Build a small zlib
CPPFLAGS+=	-DSLOW -DSMALL -DNOBYFOUR -DNO_GZIP
CPPFLAGS+=	-DDYNAMIC_CRC_TABLE -DBUILDFIXED
SRCS+=		crc32.c infback.c inffast.c inflate.c inftrees.c

CLEANFILES+=	${ZLIB_CLEANFLS}

beforedepend: ${ZLIB_GENHDRS}

# stand routines
SRCS+=	alloc.c exit.c getfile.c gets.c globals.c \
	printf.c snprintf.c strerror.c

# io routines
SRCS+=	close.c closeall.c dev.c disklabel.c dkcksum.c fstat.c ioctl.c lseek.c \
	open.c read.c stat.c write.c cread.c

# network routines
SRCS+=	arp.c ether.c in_cksum.c net.c netif.c rpc.c

# network info services
SRCS+=	bootp.c bootparam.c rarp.c

# boot filesystems
SRCS+=	ufs.c nfs.c cd9660.c ustarfs.c

${OBJS}:	${.CURDIR}/../Makefile.inc

NOPIC=	yes

install:

.include <bsd.lib.mk>
