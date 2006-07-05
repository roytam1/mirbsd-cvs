# $MirOS: src/usr.sbin/makefs/Makefile,v 1.2 2006/07/05 15:12:37 tg Exp $
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

CPPFLAGS+=	\
		-I${LSSRC} -I${MKNODSRC} -I${MTREESRC} -I${CD9660SRC}
.PATH:		${.CURDIR}/ffs ${UFSSRC}/ffs \
		${.CURDIR}/cd9660 ${CD9660SRC} \
		${LSSRC} ${MKNODSRC} ${MTREESRC}

.include <bsd.prog.mk>
