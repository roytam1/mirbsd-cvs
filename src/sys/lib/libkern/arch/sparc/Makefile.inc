# $MirOS: src/sys/lib/libkern/arch/sparc/Makefile.inc,v 1.6 2008/08/01 18:09:41 tg Exp $
# $OpenBSD: Makefile.inc,v 1.11 2003/06/01 17:00:31 deraadt Exp $
# $NetBSD: Makefile.inc,v 1.12 1996/04/23 23:05:22 christos Exp $

SRCS+=  __main.c imax.c imin.c lmax.c lmin.c max.c min.c ulmax.c ulmin.c \
	strncmp.c \
	strncpy.c scanc.c skpc.c \
	strncasecmp.c
