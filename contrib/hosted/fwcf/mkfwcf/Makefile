# $MirOS: contrib/hosted/fwcf/mkfwcf/Makefile,v 1.10 2006/09/23 20:20:01 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		mkfwcf
SRCS=		${PROG}.c ${COMPRESSORS} sys_bsd.c
NOMAN=		yes
DPADD+=		${LIBZ}
LDADD+=		-lz
CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/tesz.out \
		${.CURDIR}/test.nil ${.CURDIR}/tesz.nil

test: ${PROG}
	./${PROG} -o ${.CURDIR}/test.out ${.CURDIR}/CVS
	./${PROG} -C 1 -o ${.CURDIR}/tesz.out ${.CURDIR}/CVS
	./${PROG} -eo ${.CURDIR}/test.nil ${.CURDIR}/CVS
	./${PROG} -eC 1 -o ${.CURDIR}/tesz.nil ${.CURDIR}/CVS

.include <bsd.prog.mk>
