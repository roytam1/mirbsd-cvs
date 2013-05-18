# $MirOS$
# $OpenBSD: Makefile,v 1.5 2003/07/19 00:03:51 david Exp $
# $NetBSD: Makefile,v 1.1 1996/02/21 02:45:47 jtk Exp $

MAN+=	i386_get_ldt.2 i386_iopl.2 i386_get_ioperm.2 i386_vm86.2
MLINKS+=i386_get_ldt.2 i386_set_ldt.2 \
	i386_get_ioperm.2 i386_set_ioperm.2

.PATH: ${LIBC}/i386
NOPIC=	yes
SRCS+=	i386_get_ldt.c i386_set_ldt.c \
	i386_iopl.c i386_get_ioperm.c i386_set_ioperm.c \
	i386_vm86.c

.include <bsd.lib.mk>
