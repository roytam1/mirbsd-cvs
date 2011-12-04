# $MirOS$
# $OpenBSD: Makefile,v 1.4 2000/03/02 00:29:51 todd Exp $

# libresolv no longer needs a special version of the resolver routines.
# The resolver is always in libc.
# However, an empty library must exist in case something tries to use it.

NOPIC=	yes
LIB=	resolv
SRCS=	nothing.c

# libdl has been merged into libc (stubs) and ld.so (functions);
# however clueless people write GNU autoconf scripts which break
# dynamic loading altogether if dlopen() can't be found in libdl
# (i.e. also if libdl is missing).

afterinstall:
	-cd ${DESTDIR}${LIBDIR}; ln -f libresolv.a libdl.a

.include <bsd.lib.mk>
