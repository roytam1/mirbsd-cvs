# $OpenBSD: Makefile,v 1.22 2003/05/23 05:03:46 pvalchev Exp $
#
# If you are getting compile errors like these:
#     Undefined symbol `_postOutOfMemory' referenced from text segment
#     Undefined symbol `_PtrClass' referenced from text segment
# please read the file pkg/COMPILATION

# This port REQUIRES shared libs, and will not work without them
# (dynamic linking is an essential element of Java).
# At present it is only known to work on i386. 
# Builds nicely, but does not run at all, on sparc (gets 
# nullpointerexceptions everywhere).
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386 # *:*:sparc *:*:m68k

COMMENT=			Transvirtual's Java JDK1.1 compiler, runtime and libs

DISTNAME=	kaffe-1.0.6
CATEGORIES=	lang

MASTER_SITES=	ftp://ftp.kaffe.org/pub/kaffe/

BUILD_DEPENDS=	::devel/libtool
# Note that "lesstif" is NOT a dependency: Kaffe has its own, Motifless, AWT.
# You must have the X11 client packages installed; no good way to DEPEND this
# (if you don't, I think it will build a command-line-only Java--untested).
LIB_DEPENDS=	jpeg.62.::graphics/jpeg \
		ungif.5.::graphics/libungif \
		png.2.::graphics/png \
		gmp.4.::devel/gmp

HOMEPAGE=	http://www.kaffe.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

# build/configuration variables
USE_CXX=	Yes
USE_X11=	Yes
CONFIGURE_STYLE=gnu
CONFIGURE_ARGS+=${CONFIGURE_SHARED} --enable-static

post-install:
	@${INSTALL_DATA} ${WRKSRC}/FAQ/FAQ.* ${PREFIX}/share/kaffe

.include <bsd.port.mk>
