# $MirOS: src/lib/libc/arch/i386/Makefile.inc,v 1.3 2006/11/21 02:38:32 tg Exp $
# $OpenBSD: Makefile.inc,v 1.2 1996/08/19 08:12:11 tholo Exp $

KMINCLUDES= arch/i386/SYS.h arch/i386/DEFS.h
KMSRCS=	memcmp.S bzero.S ffs.S strcmp.S strlen.S htonl.S
