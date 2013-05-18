# $MirOS: ports/archivers/p5-Compress-Zlib/Makefile,v 1.4 2006/03/24 17:26:24 bsiegert Exp $
# $OpenBSD: Makefile,v 1.36 2004/02/16 05:31:44 kevlo Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			perl interface to the zlib compression library
DISTNAME=	Compress-Zlib-1.41
PKGNAME=	p5-${DISTNAME}-0
CATEGORIES=	archivers perl5

MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=Compress/}

# Perl
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

CONFIGURE_STYLE= perl
EXAMPLE_FILES=	filtdef filtinf gzcat gzgrep gzstream

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/p5-Compress-Zlib
.for i in ${EXAMPLE_FILES}
	${INSTALL_SCRIPT} ${WRKBUILD}/examples/$i \
		${PREFIX}/share/examples/p5-Compress-Zlib
.endfor

.include <bsd.port.mk>
