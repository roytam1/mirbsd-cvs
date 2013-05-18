# $MirOS: ports/math/fftw/Makefile,v 1.2 2006/02/09 09:36:03 tg Exp $
# $OpenBSD: Makefile,v 1.6 2003/01/22 15:45:35 sturm Exp $
# $FreeBSD: ports/math/fftw/Makefile,v 1.11 2000/06/16 21:51:38 asami Exp $

COMMENT=			C routines for computing the Discrete Fourier Transform
DISTNAME=	fftw-2.1.3
CATEGORIES=	math
HOMEPAGE=	http://www.fftw.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.fftw.org/pub/fftw/ \
		ftp://ftp.kusastro.kyoto-u.ac.jp/pub/src/GNU/fftw/

CONFIGURE_STYLE=	autoconf

.if ${MACHINE_ARCH} == "i386"
CONFIGURE_ARGS+=	--enable-i386-hacks
.endif
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/fftw
	${INSTALL_DATA} ${WRKSRC}/doc/fftw.ps ${PREFIX}/share/doc/fftw

.include <bsd.port.mk>
