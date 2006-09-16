# $MirOS: contrib/hosted/fwcf/unfwcf/Makefile,v 1.7 2006/09/16 07:09:50 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		unfwcf
SRCS=		${PROG}.c ${COMPRESSORS}
NOMAN=		yes
DPADD+=		${LIBZ}
LDADD+=		-lz
CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/tesz.out

test: ${PROG}
	./${PROG} dummy <${.CURDIR}/../mkfwcf/test.out >${.CURDIR}/test.out
	./${PROG} dummy <${.CURDIR}/../mkfwcf/tesz.out >${.CURDIR}/tesz.out

.include <bsd.prog.mk>
