# $MirOS: contrib/hosted/fwcf/mkfwcf/Makefile,v 1.3 2006/09/16 01:06:32 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		mkfwcf
NOMAN=		yes
SRCS=		mkfwcf.c
SRCS+=		fts_subs.c ft_pack.c ft_packm.c compress.c
SRCS+=		c_null.c
#SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

#DPADD+=	${LIBZ}
#LDADD+=	-lz

CLEANFILES+=	${.CURDIR}/test.out

test: ${PROG}
	./${PROG} -o ${.CURDIR}/test.out ${.CURDIR}/CVS

.include <bsd.prog.mk>
