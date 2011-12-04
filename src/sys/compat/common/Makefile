# $MirOS: src/sys/compat/common/Makefile,v 1.2 2005/03/06 21:27:28 tg Exp $
# $OpenBSD: Makefile,v 1.19 2004/09/16 13:57:47 miod Exp $
# $NetBSD: Makefile,v 1.8 1996/05/18 15:52:19 christos Exp $

LIB=	compat
NOPIC=	Yes

MACHINE=	${XMACHINE}
MACHINE_ARCH=	${XMACHINE_ARCH}

.PATH:	${COMPATDIR}

SRCS=	compat_dir.c compat_util.c compat_vm.c kern_exit_43.c kern_gen.c \
	kern_info_09.c kern_info_43.c kern_ipc_10.c kern_ipc_23.c \
	kern_ipc_35.c kern_resource_35.c kern_resource_43.c kern_sig_43.c \
	tty_43.c uipc_syscalls_43.c vfs_syscalls_25.c vfs_syscalls_35.c \
	vfs_syscalls_43.c vm_43.c

install:

.include <bsd.lib.mk>
