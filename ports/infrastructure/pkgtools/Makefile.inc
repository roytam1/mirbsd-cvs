# $MirOS$
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:44:03 deraadt Exp $

PREFIX?=	/usr
BINDIR=		${PREFIX}/sbin
DB_DIR?=	/var/db

CPPFLAGS+=	-D_PATH_REFCNTDB=\"${DB_DIR}/shareddirs.db\"
CPPFLAGS+=	-DDEF_LOG_DIR=\"${DB_DIR}/pkg\"
CPPFLAGS+=	${INCS}

LDADD+=		${LIBS}

PORTABLE?=	no
.if ${PORTABLE:L} != "yes"
CFLAGS+=	-Wall -Werror
.endif
