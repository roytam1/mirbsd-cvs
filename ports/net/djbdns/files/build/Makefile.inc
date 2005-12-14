# $MirOS: ports/net/djbdns/files/build/Makefile.inc,v 1.1.201.1 2005/05/14 23:21:06 tg Exp $

.ifndef _DJBDNS_MAKEFILE_INC
_DJBDNS_MAKEFILE_INC=1

srcdir=		${TOP}/src
mandir=		${TOP}/man
incdir=		${TOP}/build/src

.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=	${TRUEPREFIX}
.endif

BINDIR=		${PREFIX}/bin
MANDIR=		${PREFIX}/man/cat

.PATH: ${srcdir} ${mandir} ${incdir}
CPPFLAGS+=	-I${incdir} -I${srcdir}

# datasize limit in 'run' files is too low for ld.so
# to be able to pull in libc
LDFLAGS+=       -static

.endif
