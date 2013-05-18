# $MirOS: src/sbin/disklabel/Makefile,v 1.6 2006/06/17 22:12:40 tg Exp $
# $OpenBSD: Makefile,v 1.38 2005/04/01 16:00:09 deraadt Exp $

.include <bsd.own.mk>

PROG=		disklabel
SRCS=		disklabel.c dkcksum.c editor.c manpage.c
CLEANFILES+=	manpage.c
DPADD+=		${LIBUTIL}
LDADD+=		-lutil
MAN=		disklabel.8 disklabel.5
CFLAGS+=	-Wall

.if !defined(NOMAN) || ${NOMAN:L} == "no"
manpage.c: disklabel.cat8
.endif

manpage.c:
	print 'char manpage[] = ' >$@
.if defined(NOMAN) && ${NOMAN:L} != "no"
	print -r '"no manual\n"' >>$@
.else
	col -b <disklabel.cat8 | sed -e 's/[\\"]/\\&/g' \
	    -e 's/^/"/' -e 's/$$/\\n"/' >>$@
.endif
	print ';' >>$@

.if ${MACHINE_ARCH} == "i386"
CPPFLAGS+=	-DNUMBOOT=2 -DDOSLABEL
CPPFLAGS+=	-DSEEALSO="\"fdisk(8), installboot(8)\""
.endif

.if ${MACHINE_ARCH} == "sparc"
CPPFLAGS+=	-DSEEALSO="\"installboot(8)\"" -DCYLCHECK -DAAT0
.endif

.include <bsd.prog.mk>
