# $MirOS$
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:44:03 deraadt Exp $

.if ${OStype} == "Darwin"
LOCALBASE?=	/usr/mpkg
MMAKEDIR=	${LOCALBASE}/share/mmake
PREFIX?=	${LOCALBASE}
MANDIR=		${LOCALBASE}/man/cat
INCS=		-I${MMAKEDIR}
LIBS=		${MMAKEDIR}/libhash.a
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
