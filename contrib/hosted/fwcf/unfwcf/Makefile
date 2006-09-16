# $MirOS: contrib/hosted/fwcf/unfwcf/Makefile,v 1.4 2006/09/16 06:18:58 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		unfwcf
NOMAN=		yes
SRCS=		unfwcf.c
SRCS+=		fts_subs.c ft_dump.c compress.c header.c
SRCS+=		c_null.c
SRCS+=		c_zlib.c

CPPFLAGS+=	-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

DPADD+=		${LIBZ}
LDADD+=		-lz

CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/tesz.out

test: ${PROG}
	./${PROG} dummy <${.CURDIR}/../mkfwcf/test.out >${.CURDIR}/test.out
	./${PROG} dummy <${.CURDIR}/../mkfwcf/tesz.out >${.CURDIR}/tesz.out

.include <bsd.prog.mk>
