# $MirOS: src/sbin/fdisk/Makefile,v 1.4 2006/09/20 20:03:30 tg Exp $

.include <bsd.own.mk>

PROG=		fdisk
SRCS=		cmd.c disk.c fdisk.c mbr.c misc.c part.c user.c manpage.S
MAN=		fdisk.8
DPADD+=		${LIBUTIL}
LDADD+=		-lutil
COPTS+=		-Wall

.if !defined(NOMAN) || ${NOMAN:L} == "no"
manpage.o: fdisk.cat8
.else
AFLAGS_manpage.o+= -DNOMAN
.endif

.include <bsd.prog.mk>
