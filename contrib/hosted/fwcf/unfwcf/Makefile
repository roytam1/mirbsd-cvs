# $MirOS: contrib/hosted/fwcf/unfwcf/Makefile,v 1.2 2006/09/15 20:11:18 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		unfwcf
NOMAN=		yes
SRCS=		unfwcf.c
SRCS+=		fts_subs.c ft_pack.c ft_packm.c compress.c header.c
SRCS+=		c_null.c
SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

DPADD+=		${LIBZ}
LDADD+=		-lz

CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/testz.out

test: ${PROG}
	./${PROG} dummy <${.CURDIR}/../mkfwcf/test.out >${.CURDIR}/test.out
	./${PROG} dummy <${.CURDIR}/../mkfwcf/testz.out >${.CURDIR}/testz.out

.include <bsd.prog.mk>
