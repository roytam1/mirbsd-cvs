# $MirOS: src/sys/lib/libkern/arch/i386/Makefile.inc,v 1.2 2005/03/06 21:28:06 tg Exp $
# $OpenBSD: Makefile.inc,v 1.8 2003/06/01 17:00:30 deraadt Exp $
# $NetBSD: Makefile.inc,v 1.10 1996/04/13 01:17:41 cgd Exp $

SRCS+=	__main.c imax.c imin.c lmax.c lmin.c max.c min.c ulmax.c ulmin.c \
	memchr.S memcmp.S \
	bcmp.S ffs.S memset.S strcmp.S strlfun.c \
	strlen.S strncmp.c \
	strncpy.c scanc.S skpc.S locc.S htonl.S \
	strncasecmp.c
