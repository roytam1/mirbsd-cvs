# $MirOS: src/usr.sbin/pwd_mkdb/Makefile,v 1.6 2009/03/29 13:04:25 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/06/27 20:01:59 art Exp $

PROG=		pwd_mkdb
MAN=		pwd_mkdb.8
LDADD+=		-lutil
DPADD+=		${LIBUTIL}

LDSTATIC=	-static

.ifdef SMALL
BSIZE?=		1024
NELEM?=		32
CPPFLAGS+=	-DPWD_MKDB_FOR_BSD_RD -DBSIZE=${BSIZE} -DNELEM=${NELEM}
PROG=		pwd_mkdb_${BSIZE}_${NELEM}
NOMAN=		Yes

pwd_mkdb_${BSIZE}_${NELEM}.c: pwd_mkdb.c
	@cp $> $@
.endif

.include <bsd.prog.mk>
