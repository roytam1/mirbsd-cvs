# $MirOS$
# $OpenBSD: Makefile,v 1.3 1996/08/26 07:00:30 deraadt Exp $

PROG=		pkg_info
SRCS=		main.c perform.c show.c
CPPFLAGS+=	${DEBUG} -I${.CURDIR}/../lib

.include <bsd.obj.mk>

.if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=		-L${.CURDIR}/../lib/${__objdir} -linstall
DPADD+=		${.CURDIR}/../lib/${__objdir}/libinstall.a
.else
LDADD+=		-L${.CURDIR}/../lib -linstall
DPADD+=		${.CURDIR}/../lib/libinstall.a
.endif

.include <bsd.prog.mk>
