# $MirOS: ports/infrastructure/pkgtools/Makefile.inc,v 1.5 2005/05/23 11:02:41 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:44:03 deraadt Exp $

.ifndef _MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC
_MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC=1

.if ${OStype} == "Darwin"
LOCALBASE?=	/usr/mpkg
PREFIX?=	${LOCALBASE}
MANDIR=		${LOCALBASE}/man/cat
INCS=		-I${.SYSMK}
LIBS=		${.SYSMK}/libhash.a
PORTABLE=	Yes
DB_DIR?=	${LOCALBASE}/db
.else
PREFIX?=	/usr
DB_DIR?=	/var/db
.endif

BINDIR=		${PREFIX}/sbin

CPPFLAGS+=	-D_PATH_REFCNTDB=\"${DB_DIR}/shareddirs.db\"
CPPFLAGS+=	-DDEF_LOG_DIR=\"${DB_DIR}/pkg\"
CPPFLAGS+=	${INCS}

LDADD+=		${LIBS}

PORTABLE?=	no
.if ${PORTABLE:L} != "yes"
CFLAGS+=	-Wall -Werror
.endif
CDIAGFLAGS+=	-Wno-unreachable-code

.endif
