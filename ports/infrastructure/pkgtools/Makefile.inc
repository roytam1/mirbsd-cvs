# $MirOS: ports/infrastructure/pkgtools/Makefile.inc,v 1.3 2005/04/11 21:05:02 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1997/09/21 11:44:03 deraadt Exp $

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

.ifdef CRAZY
CFLAGS+=	-Wall -Wextra -Wunused -Wdeclaration-after-statement -Wundef \
		-Wendif-labels -Wshadow -Wpointer-arith -Wbad-function-cast \
		-Wcast-qual -Wcast-align -Wwrite-strings -Wstrict-prototypes \
		-Wold-style-definition -Wmissing-prototypes \
		-Wmissing-declarations -Wmissing-noreturn \
		-Wmissing-format-attribute -Wredundant-decls \
		-Wno-unreachable-code -Winline -pedantic -std=c99
.endif
