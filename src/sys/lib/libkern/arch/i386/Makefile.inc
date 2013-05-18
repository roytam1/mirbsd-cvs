# $MirOS: src/sys/lib/libkern/arch/i386/Makefile.inc,v 1.6 2007/02/06 16:24:44 tg Exp $
# $OpenBSD: Makefile.inc,v 1.8 2003/06/01 17:00:30 deraadt Exp $
# $NetBSD: Makefile.inc,v 1.10 1996/04/13 01:17:41 cgd Exp $

SRCS+=	__main.c imax.c imin.c lmax.c lmin.c max.c min.c ulmax.c ulmin.c \
	memchr.S memcmp.S \
	ffs.S memset.S strcmp.S \
	strncmp.c \
	strncpy.c scanc.S skpc.S locc.S \
	strncasecmp.c
