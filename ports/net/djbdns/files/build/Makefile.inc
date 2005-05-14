# $MirOS$

.ifndef _DJBDNS_MAKEFILE_INC
_DJBDNS_MAKEFILE_INC=1

srcdir=		${TOP}/src
mandir=		${TOP}/man

.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=	${TRUEPREFIX}
.endif

BINDIR=		${PREFIX}/bin
MANDIR=		${PREFIX}/man/cat

.PATH: ${srcdir} ${mandir}

# datasize limit in 'run' files is too low for ld.so
# to be able to pull in libc
LDFLAGS+=       -static

.endif
