# $MirOS: src/bin/ed/Makefile,v 1.3 2011/04/09 16:28:48 tg Exp $
# $OpenBSD: Makefile,v 1.11 2014/05/24 01:35:55 daniel Exp $

PROG=		ed
SRCS=		buf.c glbl.c io.c main.c re.c sub.c undo.c
CPPFLAGS+=	-DBACKWARDS

# These just get installed verbatim
.if make(install)
SUBDIR+= USD.doc/09.edtut USD.doc/10.edadv
.endif

.include <bsd.prog.mk>
