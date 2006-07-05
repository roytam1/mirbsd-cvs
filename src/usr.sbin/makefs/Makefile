# $MirOS: src/usr.sbin/makefs/Makefile,v 1.5 2006/07/05 16:24:29 tg Exp $
# $NetBSD: Makefile,v 1.19 2006/05/12 01:18:25 mrg Exp $

.include <bsd.own.mk>

PROG=	makefs
SRCS=	buf.c \
	cd9660.c cd9660_strings.c cd9660_debug.c cd9660_eltorito.c \
	cd9660_write.c cd9660_conversion.c iso9660_rrip.c \
	ffs.c ffs_alloc.c ffs_balloc.c ffs_bswap.c ffs_subr.c ffs_tables.c \
	getid.c \
	makefs.c misc.c mkfs.c \
	pack_dev.c \
	spec.c stat_flags.c \
	ufs_bmap.c \
	walk.c
MAN=	makefs.8

LSSRC=		${BSDSRCDIR}/bin/ls
MKNODSRC=	${BSDSRCDIR}/sbin/mknod
MTREESRC=	${BSDSRCDIR}/usr.sbin/mtree
UFSSRC=		${BSDSRCDIR}/sys/ufs
CD9660SRC=	${BSDSRCDIR}/sys/isofs/cd9660

CPPFLAGS+=	-DHAVE_STRUCT_STAT_BIRTHTIME=0
CPPFLAGS+=	-DHAVE_FSTATVFS=0

NBASSOC=	${.CURDIR}/nbsrc

CPPFLAGS+=	\
		-I${NBASSOC}/sys \
		-I${NBASSOC}/bin/ls -I${LSSRC} \
		-I${NBASSOC}/sbin/mknod -I${MKNODSRC} \
		-I${NBASSOC}/usr.sbin/mtree -I${MTREESRC} \
		-I${NBASSOC}/sys/isofs/cd9660 -I${CD9660SRC}
.PATH:		${.CURDIR}/ffs ${NBASSOC}/sys/ufs/ffs ${UFSSRC}/ffs \
		${.CURDIR}/cd9660 ${NBASSOC}/sys/isofs/cd9660 ${CD9660SRC} \
		${NBASSOC}/bin/ls ${LSSRC} \
		${NBASSOC}/sbin/mknod ${MKNODSRC} \
		${NBASSOC}/usr.sbin/mtree ${MTREESRC}

.include <bsd.prog.mk>
