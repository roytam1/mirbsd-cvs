# $MirOS$

PROG=		jmdict_import
SRCS=		jmdict_import.cc kana2romaji.cc
NOMAN=		Yes

LDADD=		-lsqlite -lexpat

.include <bsd.prog.mk>
