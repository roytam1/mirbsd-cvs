# $MirOS: contrib/hosted/fwcf/unfwcf/Makefile,v 1.10 2006/09/23 19:47:40 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		unfwcf
SRCS=		${PROG}.c ${COMPRESSORS} sys_bsd.c
NOMAN=		yes
DPADD+=		${LIBZ}
LDADD+=		-lz
CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/tesz.out

test: ${PROG}
	./${PROG} -d <${.CURDIR}/../mkfwcf/test.out >${.CURDIR}/test.out
	./${PROG} -d <${.CURDIR}/../mkfwcf/tesz.out >${.CURDIR}/tesz.out
	./${PROG} -i ${.CURDIR}/../mkfwcf/test.out out.test
	./${PROG} -i ${.CURDIR}/../mkfwcf/tesz.out out.tesz

.include <bsd.prog.mk>

clean: clean-local

clean-local:
	-rm -rf out.test out.tesz
