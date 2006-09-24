# $MirOS: contrib/hosted/fwcf/mkfwcf/Makefile,v 1.12 2006/09/23 23:04:16 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		fwcf_tool
SRCS=		tool.c ${COMPRESSORS} sys_bsd.c
NOMAN=		yes
DPADD+=		${LIBZ}
LDADD+=		-lz
CLEANFILES+=	${.CURDIR}/test_c.out ${.CURDIR}/tesz_c.out \
		${.CURDIR}/test_c.nil ${.CURDIR}/tesz_c.nil \
		${.CURDIR}/test_d.out ${.CURDIR}/tesz_d.out \
		${.CURDIR}/test_d.nil ${.CURDIR}/tesz_d.nil \
		${.CURDIR}/test_r.out ${.CURDIR}/tesz_r.out \
		${.CURDIR}/test_r.nil ${.CURDIR}/tesz_r.nil

test: ${PROG}
	./${PROG} -Mo ${.CURDIR}/test_c.out ${.CURDIR}/../mkfwcf/CVS
	./${PROG} -MC 1 -o ${.CURDIR}/tesz_c.out ${.CURDIR}/../mkfwcf/CVS
	./${PROG} -Meo ${.CURDIR}/test_c.nil
	./${PROG} -MeC 1 -o ${.CURDIR}/tesz_c.nil
	./${PROG} -Ud <${.CURDIR}/test_c.out >${.CURDIR}/test_d.out
	./${PROG} -Ud <${.CURDIR}/tesz_c.out >${.CURDIR}/tesz_d.out
	./${PROG} -Ud <${.CURDIR}/test_c.nil >${.CURDIR}/test_d.nil
	./${PROG} -Ud <${.CURDIR}/tesz_c.nil >${.CURDIR}/tesz_d.nil
	./${PROG} -Ui ${.CURDIR}/test_c.out out.test
	./${PROG} -Ui ${.CURDIR}/tesz_c.out out.tesz
.ifndef notyet
	./${PROG} -Ri ${.CURDIR}/tesz_c.out -o ${.CURDIR}/test_r.out
	./${PROG} -Ri ${.CURDIR}/tesz_c.nil -o ${.CURDIR}/test_r.nil
	./${PROG} -Rci ${.CURDIR}/test_c.out -o ${.CURDIR}/tesz_r.out
	./${PROG} -Rci ${.CURDIR}/test_c.nil -o ${.CURDIR}/tesz_r.nil
.else
	./${PROG} -Ri ${.CURDIR}/test_c.out -o ${.CURDIR}/test_r.out
	./${PROG} -Ri ${.CURDIR}/test_c.nil -o ${.CURDIR}/test_r.nil
	./${PROG} -Rci ${.CURDIR}/tesz_c.out -o ${.CURDIR}/tesz_r.out
	./${PROG} -Rci ${.CURDIR}/tesz_c.nil -o ${.CURDIR}/tesz_r.nil
.endif

.include <bsd.prog.mk>

clean: clean-local

clean-local:
	-rm -rf out.test out.tesz
