# $MirOS: contrib/hosted/fwcf/Makefile.inc,v 1.4 2006/09/24 20:34:59 tg Exp $

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
CFLAGS_c_lzo1x1.o+=	-I${.CURDIR}/../bundled -Wno-undef

.if make(test)
CFLAGS_sys_bsd.o+=	-DRND_DISABLE
.endif
