# $MirOS$

.include <bsd.own.mk>

PROG=		fdisk
MAN=		fdisk.8
SRCS=		cmd.c disk.c fdisk.c mbr.c misc.c part.c user.c manpage.c
CLEANFILES+=	manpage.c

MBRPATH=	../bootsys/common/dosmbr
CPPFLAGS+=	-I${.OBJDIR}/${MBRPATH}
CFLAGS+=	-Wall -Werror
.PATH: ${.OBJDIR}/${MBRPATH}

${.OBJDIR}/${MBRPATH}/mbrcode.h:
	cd ${.CURDIR}/${MBRPATH} && ${MAKE} _DEP=1 $@

fdisk.o: ${.OBJDIR}/${MBRPATH}/mbrcode.h

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
