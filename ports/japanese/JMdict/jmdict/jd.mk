# $MirOS$

PROG=		jmdict
SRCS=		jmdict.cc
NOMAN=		Yes

LDADD=		-lsqlite

.include <bsd.prog.mk>
