# $MirOS: src/sys/compat/openbsd/Makefile,v 1.1.7.1 2005/03/06 16:33:43 tg Exp $
# $OpenBSD: Makefile,v 1.3 2001/08/26 03:23:44 deraadt Exp $
# $NetBSD: Makefile,v 1.1 1995/02/28 23:26:21 fvdl Exp $

DEP=	../../kern/makesyscalls.sh syscalls.conf syscalls.master
EM=	openbsd
OBJS=	${EM}_sysent.c ${EM}_syscalls.c ${EM}_syscall.h ${EM}_syscallargs.h

${OBJS}: ${DEP}
	${SHELL} ${DEP}

cleangen::
	-rm -f ${OBJS}
