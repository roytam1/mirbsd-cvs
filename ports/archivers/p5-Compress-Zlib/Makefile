# $MirOS: ports/archivers/p5-Compress-Zlib/Makefile,v 1.5 2006/09/14 00:06:51 tg Exp $
# $OpenBSD: Makefile,v 1.36 2004/02/16 05:31:44 kevlo Exp $

COMMENT=		perl interface to the zlib compression library
DISTNAME=		Compress-Zlib-2.015
PKGNAME=		p5-${DISTNAME}-${DASH_VER}
CATEGORIES=		archivers perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=Compress/}

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

B_R_DEPENDS=		:p5-IO-Compress-Zlib->=2.015:archivers/p5-IO-Compress-Zlib

CONFIGURE_STYLE=	perl
PKG_ARCH=		*
EXAMPLE_FILES=		filtdef filtinf gzcat gzgrep gzstream

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/p5-Compress-Zlib
.for i in ${EXAMPLE_FILES}
	${INSTALL_SCRIPT} ${WRKBUILD}/examples/$i \
		${PREFIX}/share/examples/p5-Compress-Zlib
.endfor

.include <bsd.port.mk>
