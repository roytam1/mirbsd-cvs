# $MirOS: src/sbin/fdisk/Makefile,v 1.2 2005/03/06 19:49:54 tg Exp $

.include <bsd.own.mk>

PROG=		fdisk
MAN=		fdisk.8
SRCS=		cmd.c disk.c fdisk.c mbr.c misc.c part.c user.c manpage.c
CLEANFILES+=	manpage.c
CFLAGS+=	-Wall

DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.if !defined(NOMAN) || ${NOMAN:L} == "no"
manpage.c: fdisk.cat8
.endif

manpage.c:
	print 'char manpage[] = ' >$@
.if defined(NOMAN) && ${NOMAN:L} != "no"
	print -r '"no manual\n"' >>$@
.else
	col -b <fdisk.cat8 | sed -e 's/[\\"]/\\&/g' \
	    -e 's/^/"/' -e 's/$$/\\n"/' >>$@
.endif
	print ';' >>$@

.include <bsd.prog.mk>
