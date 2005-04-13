# $MirOS: src/usr.bin/oldroff/hunt/Makefile,v 1.1.7.1 2005/03/06 16:56:01 tg Exp $
# @(#)Makefile	5.3 (Berkeley) 11/14/91

PROG=	hunt
SRCS=	deliv2.c glue4.c glue5.c hunt1.c hunt2.c hunt3.c hunt5.c hunt6.c \
	hunt7.c hunt8.c hunt9.c refer3.c shell.c tick.c
NOMAN=	yes

CPPFLAGS+=	-I${.CURDIR}/../refer
.PATH:	${.CURDIR}/../deliv ${.CURDIR}/../refer

.if ${OStype} != "Interix"
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
.endif

.include <bsd.prog.mk>
