# $MirOS: src/sbin/disklabel/Makefile,v 1.9 2007/09/18 20:31:56 tg Exp $
# $OpenBSD: Makefile,v 1.38 2005/04/01 16:00:09 deraadt Exp $

.include <bsd.own.mk>

PROG=		disklabel
SRCS=		disklabel.c dkcksum.c editor.c manpage.S
DPADD+=		${LIBMBFUN} ${LIBUTIL}
LDADD+=		-lmbfun -lutil
MAN=		disklabel.8 disklabel.5
COPTS+=		-Wall

.if !defined(NOMAN) || ${NOMAN:L} == "no"
manpage.o: disklabel.cat8
.else
AFLAGS_manpage.o+= -DNOMAN
.endif

.if ${MACHINE_ARCH} == "i386"
CPPFLAGS+=	-DNUMBOOT=2 -DDOSLABEL
CPPFLAGS+=	-DSEEALSO="\"fdisk(8), installboot(8)\""
.endif

.if ${MACHINE_ARCH} == "sparc"
CPPFLAGS+=	-DSEEALSO="\"installboot(8)\"" -DCYLCHECK -DAAT0
.endif

.include <bsd.prog.mk>
