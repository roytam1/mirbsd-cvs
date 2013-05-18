# $MirOS: src/bin/md5/Makefile,v 1.12 2008/03/09 14:18:58 tg Exp $
# $OpenBSD: Makefile,v 1.10 2005/05/24 21:57:47 millert Exp $

PROG=	cksum
MAN=	cksum.1 md5.1 sha1.1 rmd160.1
LINKS=	${BINDIR}/cksum ${BINDIR}/sha1 \
	${BINDIR}/cksum ${BINDIR}/rmd160 \
	${BINDIR}/cksum ${BINDIR}/md5 \
	${BINDIR}/cksum ${BINDIR}/sum
MLINKS= cksum.1 sum.1

.if exists(${.SYSMK}/libmirmake.a)
CPPFLAGS+=	-D_GNU_SOURCE -D_MIRMAKE_DEFNS
LDADD+=		-L${.SYSMK} -lmirmake
.endif

.include <bsd.prog.mk>
