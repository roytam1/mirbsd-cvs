# $MirOS: src/libexec/cpp/Makefile,v 1.7 2008/11/22 13:08:48 tg Exp $
# @(#)Makefile	5.2 (Berkeley) 5/12/90

PROG=		cpp
SRCS=		cpp.c cpy.y
NOMAN=		yes

.include <bsd.own.mk>

CPPFLAGS+=	-Dunix -DFLEXNAMES
COPTS+=		-std=gnu89

.include <bsd.prog.mk>
