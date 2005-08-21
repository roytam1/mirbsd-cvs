# $MirOS: ports/infrastructure/pkgtools/Makefile.inc,v 1.7 2005/08/20 12:33:54 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:44:03 deraadt Exp $

.ifndef _MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC
_MODPORTS_INFRASTRUCTURE_PKGTOOLS_MAKEFILE_INC=1

# Where MirPorts live
LOCALBASE?=	/usr/mpkg

# Where we live
PREFIX?=	${LOCALBASE}
# Where we place our database
DB_DIR?=	${LOCALBASE}/db


BINDIR=		${PREFIX}/sbin
.if ${PREFIX} == "/usr"
MANDIR=		${PREFIX}/share/man/cat
.else
MANDIR=		${PREFIX}/man/cat
.endif

.if ${OStype} != "MirBSD"
PORTABLE=	Yes
.endif

.if (${OStype} == "Darwin") || (${OStype} == "Interix")
CPPFLAGS+=	-I${.SYSMK}
LDADD+=		-L\${.SYSMK} -lmirmake
.endif

.if ${OStype} == "Interix"
LDADD+=		-ldb
NEED_COMPAT=	Yes
.endif

CPPFLAGS+=	-D_PATH_REFCNTDB=\"${DB_DIR}/shareddirs.db\"
CPPFLAGS+=	-DDEF_LOG_DIR=\"${DB_DIR}/pkg\"

PORTABLE?=	no
.if ${PORTABLE:L} != "yes"
CFLAGS+=	-Wall -Werror
.endif
CDIAGFLAGS+=	-Wno-unreachable-code

.endif
