# $MirOS: contrib/hosted/fwcf/fwcf.helper/Makefile,v 1.2 2006/09/24 03:25:12 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

PROG=		fwcf.helper
SRCS=		${PROG}.c c_zlib.c sys_bsd.c
NOMAN=		Yes
DPADD+=		${LIBZ}
LDADD+=		-lz
SRCS+=		compress.c
SRCS+=		cpr_get.c
SRCS+=		cpr_list.c
SRCS+=		cpr_lsth.c
SRCS+=		ft_creat.c
SRCS+=		ft_pack.c
SRCS+=		ft_packm.c
SRCS+=		fts_subs.c
SRCS+=		header.c
SRCS+=		unwraps.c
SRCS+=		wraps.c
CLEANFILES+=	${.CURDIR}/test.out ${.CURDIR}/test.nil

LIB=		# don't need, thanks

test: ${PROG}
	./${PROG} -M ${.CURDIR}/../mkfwcf/CVS >${.CURDIR}/test.out
	./${PROG} -Me >${.CURDIR}/test.nil
#	./${PROG} -U out.test <${.CURDIR}/../mkfwcf/test.out
	./${PROG} -U out.tesz <${.CURDIR}/../mkfwcf/tesz.out

.include <bsd.prog.mk>

clean: clean-local

clean-local:
	-rm -rf out.test out.tesz
