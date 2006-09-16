# $MirOS: contrib/hosted/fwcf/mkfwcf/Makefile,v 1.2 2006/09/15 20:11:18 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		mkfwcf
NOMAN=		yes
SRCS=		mkfwcf.c
SRCS+=		fts_subs.c ft_pack.c compress.c
SRCS+=		c_null.c
#SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

#DPADD+=	${LIBZ}
#LDADD+=	-lz

.include <bsd.prog.mk>
