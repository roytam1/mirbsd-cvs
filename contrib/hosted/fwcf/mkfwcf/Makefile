# $MirOS: contrib/hosted/fwcf/mkfwcf/Makefile,v 1.1 2006/09/15 20:09:37 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		mkfwcf
NOMAN=		yes
SRCS=		mkfwcf.c
SRCS+=		fts_subs.c ft_pack.c compress.c
SRCS+=		c_none.c
#SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

#DPADD+=	${LIBZ}
#LDADD+=	-lz

.include <bsd.prog.mk>
