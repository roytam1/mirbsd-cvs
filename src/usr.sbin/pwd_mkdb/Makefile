# $MirOS: src/usr.sbin/pwd_mkdb/Makefile,v 1.4 2008/03/27 14:53:25 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/06/27 20:01:59 art Exp $

PROG=		pwd_mkdb
MAN=		pwd_mkdb.8
LDADD+=		-lutil
DPADD+=		${LIBUTIL}
BINDIR?=	/usr/dsbin

.ifdef SMALL
BSIZE?=		256
NELEM?=		32
CPPFLAGS+=	-DPWD_MKDB_FOR_BSD_RD -DBSIZE=${BSIZE} -DNELEM=${NELEM}
PROG=		pwd_mkdb_${BSIZE}_${NELEM}
NOMAN=		Yes

pwd_mkdb_${BSIZE}_${NELEM}.c: pwd_mkdb.c
	@cp $> $@
.endif

.include <bsd.prog.mk>
