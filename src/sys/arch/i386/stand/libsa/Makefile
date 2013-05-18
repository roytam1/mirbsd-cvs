# $MirOS: src/sys/arch/i386/stand/libsa/Makefile,v 1.19 2008/08/01 18:09:31 tg Exp $
# $OpenBSD: Makefile,v 1.47 2007/05/30 01:25:43 tom Exp $

.include "${.CURDIR}/../Makefile.inc"

LIB=		sa
S=		${.CURDIR}/../../../..
SADIR=		${.CURDIR}/..
DIR_SA=		$S/lib/libsa
DIR_KERN=	$S/lib/libkern
CPPFLAGS+=	-DLINKADDR=${LINKADDR} -DHEAP_LIMIT=${HEAP_LIMIT}
CPPFLAGS+=	-I$S/stand/boot -I$S/lib/libsa
CPPFLAGS+=	-D__INTERNAL_LIBSA_CREAD #-DCOMPAT_UFS
CPPFLAGS+=	${SACFLAGS:M-[DI]*}
COPTS+=		${SACFLAGS:N-[DI]*} ${DEBUGFLAGS}
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

CPPFLAGS+=	-DZCONST=const
HOSTCPPFLAGS+=	-DZCONST=const
CLEANFILES+=	${ZLIB_CLEANFLS}

beforedepend: ${ZLIB_GENHDRS}

# i386 stuff (so, it will possibly load in the same 64k)
SRCS+=	machdep.c dev_i386.c exec_i386.c cmd_i386.c loadfile.c

SRCS+=	gidt.S debug_i386.S alloca.S toridev.c \
	biosdev.c bioscons.c gateA20.c apmprobe.c \
	memprobe.c diskprobe.c pciprobe.c smpprobe.c \
	cpuprobe.c time.c biosprobe.c \
	ps2probe.c pxe.c pxe_net.c pxe_call.S

# stand routines
SRCS+=	alloc.c exit.c getfile.c gets.c globals.c \
	strncmp.c printf.c snprintf.c memcpy.c \
	strerror.c strncpy.c strtol.c strtoll.c ctime.c

# io routines
SRCS+=	close.c closeall.c dev.c disklabel.c dkcksum.c fstat.c ioctl.c lseek.c \
	open.c read.c stat.c write.c cread.c readdir.c cons.c

# network routines
SRCS+=	arp.c ether.c in_cksum.c net.c netif.c rpc.c

# network info services
SRCS+=	bootp.c bootparam.c rarp.c

# boot filesystems
SRCS+=	ufs.c nfs.c tftp.c cd9660.c fat.c

# debugger
SRCS+=	debug.c

NOPIC=	yes

.PATH:  ${DIR_SA} ${DIR_KERN}

all: ${SALIB}

install:

.include <bsd.lib.mk>

#AS=cat ; 
#AS+=	-R
#AS+=	-a
