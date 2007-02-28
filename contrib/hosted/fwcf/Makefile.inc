# $MirOS: contrib/hosted/fwcf/Makefile.inc,v 1.5 2006/09/24 21:46:16 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/licence for details.

__CRAZY=		Yes
MKC_DEBG=		cpp

UNAME_S!=		uname -s

.if ${UNAME_S} == "OpenBSD"
CPPFLAGS+=		-D'__RCSID(x)=static const char __rcsid[] = (x)'
.endif

REALOBJDIR!=		readlink -nf .

.ifndef LIB
DPADD+=			${REALOBJDIR}/../lib/libfwcf.a
LDADD+=			-L${REALOBJDIR}/../lib -lfwcf
.endif

CPPFLAGS+=		-I${.CURDIR}/..
.PATH: ${.CURDIR}/..

test: .NOTMAIN all

COMPRESSORS+=		c_null.c
COMPRESSORS+=		c_zlib.c

COMPRESSORS+=		c_lzo1x1.c
MKDEP+=			-I${.CURDIR}/../bundled
CFLAGS_c_lzo1x1.o+=	-I${.CURDIR}/../bundled -Wno-undef

.if make(test)
CFLAGS_sys_bsd.o+=	-DRND_DISABLE
.endif
