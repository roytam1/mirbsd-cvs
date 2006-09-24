# $MirOS: contrib/hosted/fwcf/Makefile.inc,v 1.3 2006/09/16 07:35:36 tg Exp $

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

.if make(test)
CFLAGS_sys_bsd.o+=	-DRND_DISABLE
.endif
