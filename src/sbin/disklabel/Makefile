# $MirOS: src/sbin/disklabel/Makefile,v 1.2 2005/03/06 19:49:51 tg Exp $
# $OpenBSD: Makefile,v 1.30 2003/10/31 04:05:29 drahn Exp $

.include <bsd.own.mk>

PROG=		disklabel
SRCS=		disklabel.c dkcksum.c editor.c manpage.c
CLEANFILES+=	manpage.c
DPADD+=		${LIBUTIL}
LDADD+=		-lutil
MAN=		disklabel.8 disklabel.5
CFLAGS+=	-Wall -Werror

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

.if ${MACHINE} == "i386"
CPPFLAGS+=	-DNUMBOOT=2 -DDOSLABEL
CPPFLAGS+=	-DSEEALSO="\"fdisk(8), installboot(8)\""
.endif

.if ${MACHINE} == "sparc"
CPPFLAGS+=	-DSEEALSO="\"installboot(8)\"" -DCYLCHECK -DAAT0
.endif

.if ${MACHINE} == "macppc"
CPPFLAGS+=	-DDOSLABEL
CPPFLAGS+=	-DSEEALSO="\"fdisk(8)\""
.endif

.include <bsd.prog.mk>
