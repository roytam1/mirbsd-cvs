# $MirOS: ports/infrastructure/pkgtools/Makefile.inc,v 1.16 2008/03/12 23:46:49 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:44:03 deraadt Exp $

.ifndef _MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC
_MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC=1

LOCALBASE?=	/usr/mpkg	# overridden by setup.ksh
PKG_DB_DIR?=	${LOCALBASE}/db	# path for package databases, etc.
#				# can also be overridden by environment
BSD_PREFIX=	${LOCALBASE}	# path for binaries, man page, etc.
#				# usually not overridden

BINDIR=		${BSD_PREFIX}/sbin
CPPFLAGS+=	-D_PATH_REFCNTDB=\"${PKG_DB_DIR}/shareddirs.db\"
CPPFLAGS+=	-DDEF_LOG_DIR=\"${PKG_DB_DIR}/pkg\"

.include <bsd.own.mk>

.ifndef LIB
CPPFLAGS+=	-I${.CURDIR}/../lib

.  include <bsd.obj.mk>
.  if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=		-L${.CURDIR}/../lib/${__objdir} -linstall
DPADD+=		${.CURDIR}/../lib/${__objdir}/libinstall.a
.  else
LDADD+=		-L${.CURDIR}/../lib -linstall
DPADD+=		${.CURDIR}/../lib/libinstall.a
.  endif
.endif

.if ${OStype} != "MirBSD"
PORTABLE=	Yes
.endif

.if exists(${.SYSMK}/libmirmake.a)
CPPFLAGS+=	-I${.SYSMK}
LDADD+=		-L${.SYSMK} -lmirmake
.endif

.if ${OStype} == "Interix"
LDADD+=		-ldb
.endif

.if ${BINOWN} != "root"
CPPFLAGS+=	-DAS_USER
.endif

PORTABLE?=	no
.if ${PORTABLE:L} != "yes"
COPTS+=		-Wall -Werror
.endif

.endif
