# $MirOS$
# $OpenBSD: Makefile,v 1.2 1996/09/25 06:40:52 etheisen Exp $
# $OpenBSD: Makefile,v 1.4 2000/03/01 22:10:03 todd Exp $

PROG=		crunchgen
SRCS=		crunch.c
SRCS+=		crunchgen.c crunched_skel.c
SRCS+=		crunchide.c ecoff_hide.c elf_hide.c
CFLAGS+=	-Wall -W -pedantic
CPPFLAGS+=	-DMF_NAMES='"Makefile.bsd-wrapper","Makefile"'
CLEANFILES+=	crunched_skel.c
MAN=		crunchgen.1 crunchide.1
LINKS=		${BINDIR}/crunchgen ${BINDIR}/crunchide

crunched_skel.c: ${.CURDIR}/crunched_main.c
	${SHELL} ${.CURDIR}/mkskel.sh ${.ALLSRC} >$@

.include <bsd.prog.mk>
