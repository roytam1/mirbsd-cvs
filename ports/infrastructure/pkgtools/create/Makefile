# $MirOS: ports/infrastructure/pkgtools/create/Makefile,v 1.1.7.1.2.1 2005/09/11 00:49:39 tg Exp $
# $OpenBSD: Makefile,v 1.3 1996/08/26 07:00:30 deraadt Exp $

PROG=		pkg_create
SRCS=		main.c perform.c pl.c
CPPFLAGS+=	${DEBUG} -I${.CURDIR}/../lib

.include "../Makefile.inc"
.include <bsd.obj.mk>

.if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=		-L${.CURDIR}/../lib/${__objdir} -linstall
DPADD+=		${.CURDIR}/../lib/${__objdir}/libinstall.a
.else
LDADD+=		-L${.CURDIR}/../lib -linstall
DPADD+=		${.CURDIR}/../lib/libinstall.a
.endif

.include <bsd.prog.mk>
