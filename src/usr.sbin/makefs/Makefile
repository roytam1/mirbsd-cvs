# $MirOS: src/usr.sbin/makefs/Makefile,v 1.23 2010/03/16 22:05:54 tg Exp $
# $NetBSD: Makefile,v 1.25 2009/04/22 15:23:05 lukem Exp $

WARNS?=	3	# XXX -Wsign-compare

.include <bsd.own.mk>

PROG=	makefs
SRCS=	cd9660.c ffs.c \
	getid.c \
	makefs.c misc.c \
	pack_dev.c \
	spec.c \
	walk.c
MAN=	makefs.8

.ifdef FEDORA
DEBIAN=		implied
.endif

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

CPPFLAGS+=	-I${.CURDIR} -I${MKNODSRC} -I${MTREESRC}
.PATH:		${MKNODSRC} ${MTREESRC}

.include "cd9660/Makefile.inc"
.include "ffs/Makefile.inc"

.ifdef MAKEFS_PORT
CPPFLAGS+=	-I${NETBSDSRCDIR}/sys \
		-I${BSDSRCDIR}/sbin/mknod -I${BSDSRCDIR}/usr.sbin/mtree \
		-I${BSDSRCDIR}/sys -I${BSDSRCDIR}/sys/isofs/cd9660
.PATH:		${BSDSRCDIR}/sys/ufs/ffs ${BSDSRCDIR}/sys/isofs/cd9660 \
		${BSDSRCDIR}/sbin/mknod ${BSDSRCDIR}/usr.sbin/mtree
.endif

.if defined(DEBIAN) && !defined(FEDORA)
LDADD+=		-lbsd
.endif

.if !defined(DEBIAN) && (${HOSTPROG:U} == "")
DPADD+= ${LIBUTIL}
LDADD+= -lutil
.endif

.ifdef MAKEFS_PORT
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

.  ifdef FEDORA
CPPFLAGS+=	-DFEDORA -I${BSDSRCDIR}/include
SRCS+=		setmode.c unvis.c
.PATH: ${BSDSRCDIR}/lib/libc/gen

SRCS+=		fgetln.c
.PATH: ${BSDSRCDIR}/../contrib/code/mirmake/dist/contrib

SRCS+=		strlfun.c
.PATH: ${BSDSRCDIR}/../contrib/code/jupp
.  endif
.endif

.include <bsd.prog.mk>
