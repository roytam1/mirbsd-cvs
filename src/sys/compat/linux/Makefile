# $MirOS: src/sys/compat/linux/Makefile,v 1.2 2005/03/06 21:27:30 tg Exp $
# $OpenBSD: Makefile,v 1.3 2001/08/26 03:23:44 deraadt Exp $
# $NetBSD: Makefile,v 1.1 1995/02/28 23:26:21 fvdl Exp $

DEP=	syscalls.conf syscalls.master ../../kern/makesyscalls.sh
OBJS=	linux_sysent.c linux_syscalls.c linux_syscall.h linux_syscallargs.h

${OBJS}: ${DEP}
	${SHELL} ../../kern/makesyscalls.sh syscalls.conf syscalls.master

cleangen::
	-rm -f ${OBJS}
