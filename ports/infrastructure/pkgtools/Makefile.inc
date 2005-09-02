# $MirOS: ports/infrastructure/pkgtools/Makefile.inc,v 1.6 2005/05/23 11:59:58 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:44:03 deraadt Exp $

.ifndef _MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC
_MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC=1

NEW_LOCALBASE?=	/usr/mpkg
DB_DIR?=	${NEW_LOCALBASE}/db

LOCALBASE?=	/usr/mpkg
PREFIX?=	${LOCALBASE}
.if ${OStype} == "Darwin"
MANDIR=		${LOCALBASE}/man/cat
INCS=		-I${.SYSMK}
LIBS=		${.SYSMK}/libmirmake.a
PORTABLE=	Yes
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
