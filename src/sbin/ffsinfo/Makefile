# $MirOS$
# @(#)Makefile    8.8 (Berkeley) 6/21/2000
#
# $TSHeader: src/sbin/ffsinfo/Makefile,v 1.3 2000/12/05 19:45:10 tomsoft Exp $
# $FreeBSD: src/sbin/ffsinfo/Makefile,v 1.4 2001/12/04 02:19:46 obrien Exp $
#MAINTAINER=	tomsoft@FreeBSD.ORG, chm@FreeBSD.ORG

.PATH:	${.CURDIR}/../growfs
PROG=	ffsinfo
SRCS=	ffsinfo.c debug.c
MAN=	ffsinfo.8

CPPFLAGS+= -DFS_DEBUG -I${.CURDIR}/../growfs

.include <bsd.prog.mk>
