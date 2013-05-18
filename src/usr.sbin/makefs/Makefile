# $MirOS: src/usr.sbin/makefs/Makefile,v 1.19 2009/07/23 19:32:23 tg Exp $
# $NetBSD: Makefile,v 1.22 2008/08/29 00:02:25 gmcgarry Exp $

.include <bsd.own.mk>

PROG=	makefs
SRCS=	buf.c \
	cd9660.c cd9660_strings.c cd9660_debug.c cd9660_eltorito.c \
	cd9660_write.c cd9660_conversion.c iso9660_rrip.c \
	ffs.c ffs_alloc.c ffs_balloc.c ffs_bswap.c ffs_subr.c ffs_tables.c \
	getid.c \
	makefs.c misc.c mkfs.c \
	pack_dev.c \
	spec.c \
	ufs_bmap.c \
	walk.c
MAN=	makefs.8

OStype?=	unknown
.if (${OStype} == "MirBSD") || defined(DEBIAN)
MAKEFS_PORT=	#defined
.endif

.ifdef MAKEFS_PORT
HOSTPROG=	#defined, empty
NETBSDSRCDIR?=	${.CURDIR}/nbsrc
CDIAGFLAGS+=	-Wmissing-declarations -Wmissing-prototypes
CPPFLAGS+=	-DLIBC_SCCS -DHAVE_STRUCT_STAT_BIRTHTIME=0 \
		-DHAVE_NBTOOL_CONFIG_H=0 -DHAVE_NETDB_H=1 \
		-DHAVE_PWCACHE_USERDB=0 -DHAVE_STRSUFTOLL=0
.endif

MKNODSRC=	${NETBSDSRCDIR}/sbin/mknod
MTREESRC=	${NETBSDSRCDIR}/usr.sbin/mtree
UFSSRC=		${NETBSDSRCDIR}/sys/ufs
CD9660SRC=	${NETBSDSRCDIR}/sys/fs/cd9660

CPPFLAGS+=	-I${.CURDIR} \
		-I${MKNODSRC} -I${MTREESRC} -I${CD9660SRC}
.PATH:		${.CURDIR}/ffs ${UFSSRC}/ffs \
		${.CURDIR}/cd9660 ${CD9660SRC} \
		${MKNODSRC} ${MTREESRC}
.ifdef MAKEFS_PORT
CPPFLAGS+=	-I${NETBSDSRCDIR}/sys \
		-I${BSDSRCDIR}/sbin/mknod -I${BSDSRCDIR}/usr.sbin/mtree \
		-I${BSDSRCDIR}/sys -I${BSDSRCDIR}/sys/isofs/cd9660
.PATH:		${BSDSRCDIR}/sys/ufs/ffs ${BSDSRCDIR}/sys/isofs/cd9660 \
		${BSDSRCDIR}/sbin/mknod ${BSDSRCDIR}/usr.sbin/mtree
.endif

.ifdef DEBIAN
LDADD+=		-lbsd
.endif

.if !defined(DEBIAN) && (${HOSTPROG:U} == "")
DPADD+= ${LIBUTIL}
LDADD+= -lutil
.endif

.ifndef MAKEFS_PORT
WARNS?=	3

.if !defined(HOSTPROGNAME)
.if (defined(HAVE_GCC) && ${HAVE_GCC} == 4) || defined(HAVE_PCC)
.for f in cd9660_debug cd9660_write
COPTS.${f}.c+=  -Wno-pointer-sign
.endfor
.endif
.endif

.else	# MirBSD

SRCS+=		pwcache.c
CPPFLAGS+=	-I${NETBSDSRCDIR}/lib/libc/gen
.PATH: ${NETBSDSRCDIR}/lib/libc/gen

SRCS+=		strsuftoll.c
CPPFLAGS+=	-I${NETBSDSRCDIR}/lib/libc/stdlib
.PATH: ${NETBSDSRCDIR}/lib/libc/stdlib

.  ifdef DEBIAN
CPPFLAGS+=	-D_GNU_SOURCE -DDEBIAN
SRCS+=		fparseln.c
.PATH: ${BSDSRCDIR}/lib/libutil
.  else
SRCS+=		stat_flags.c
.PATH: ${NETBSDSRCDIR}/lib/libutil
.  endif
.endif

.include <bsd.prog.mk>
