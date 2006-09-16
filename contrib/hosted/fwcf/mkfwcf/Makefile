# $MirOS: contrib/hosted/fwcf/mkfwcf/Makefile,v 1.5 2006/09/16 04:40:25 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		mkfwcf
NOMAN=		yes
SRCS=		mkfwcf.c
SRCS+=		fts_subs.c ft_pack.c ft_packm.c compress.c header.c
SRCS+=		c_null.c
SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

DPADD+=		${LIBZ}
LDADD+=		-lz

CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/testz.out

test: ${PROG}
	./${PROG} -o ${.CURDIR}/test.out ${.CURDIR}/CVS
	./${PROG} -C 1 -o ${.CURDIR}/testz.out ${.CURDIR}/CVS

.include <bsd.prog.mk>
