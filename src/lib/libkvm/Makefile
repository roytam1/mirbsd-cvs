# $MirOS: src/lib/libkvm/Makefile,v 1.6 2013/08/05 22:06:11 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/01/08 04:59:10 millert Exp $
# $NetBSD: Makefile,v 1.11 1996/03/18 22:33:07 thorpej Exp $
# from: @(#)Makefile	8.1 (Berkeley) 6/4/93

SHLIB_VERSION?=	10.1
LIB=		kvm
CPPFLAGS+=	-DLIBC_SCCS

# Try most specific name first.
.if	exists(kvm_${MACHINE}.c)
SRCS=	kvm_${MACHINE}.c
.else
# Less specific name (i.e. m68k)
CPPFLAGS+=-D${MACHINE}
SRCS=	kvm_${MACHINE_ARCH}.c
.endif

SRCS+=	kvm.c kvm_file.c kvm_getloadavg.c kvm_proc.c

DPADD+=	${LIBZ}
LDADD+=	-lz

MAN=	kvm.3 kvm_dump.3 kvm_geterr.3 kvm_getfiles.3 kvm_getloadavg.3 \
	kvm_getprocs.3 kvm_nlist.3 kvm_open.3 kvm_read.3

MLINKS+=kvm_getprocs.3 kvm_getargv.3 kvm_getprocs.3 kvm_getenvv.3
MLINKS+=kvm_getprocs.3 kvm_getproc2.3
MLINKS+=kvm_getprocs.3 kvm_getargv2.3 kvm_getprocs.3 kvm_getenvv2.3
MLINKS+=kvm_open.3 kvm_openfiles.3 kvm_open.3 kvm_close.3
MLINKS+=kvm_read.3 kvm_write.3
MLINKS+=kvm_dump.3 kvm_dump_mkheader.3 kvm_dump.3 kvm_dump_wrtheader.3
MLINKS+=kvm_dump.3 kvm_dump_inval.3

.include <bsd.lib.mk>
