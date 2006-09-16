# $MirOS: contrib/hosted/fwcf/mkfwcf/Makefile,v 1.7 2006/09/16 06:18:58 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		mkfwcf
NOMAN=		yes
SRCS=		mkfwcf.c
SRCS+=		fts_subs.c ft_pack.c ft_packm.c compress.c header.c wraps.c
SRCS+=		c_null.c
SRCS+=		c_zlib.c

CPPFLAGS+=	-DWRAPS_PACK

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

DPADD+=		${LIBZ}
LDADD+=		-lz

CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/tesz.out

test: ${PROG}
	./${PROG} -o ${.CURDIR}/test.out ${.CURDIR}/CVS
	./${PROG} -C 1 -o ${.CURDIR}/tesz.out ${.CURDIR}/CVS

.include <bsd.prog.mk>
