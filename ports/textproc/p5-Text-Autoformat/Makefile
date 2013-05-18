# $MirOS$
# $OpenBSD: Makefile,v 1.5 2004/02/01 07:09:47 pvalchev Exp $

COMMENT=		automatic text wrapping and reformatting
VERSION=		1.14.0
DISTNAME=		Text-Autoformat-v${VERSION}
PKGNAME=		p5-Text-Autoformat-${VERSION}-${DASH_VER}
CATEGORIES=		textproc perl5

MASTER_SITES=		${MASTER_SITE_PERL_CPAN:=../by-authors/id/D/DC/DCONWAY/}
HOMEPAGE=		http://search.cpan.org/author/DCONWAY/${DISTNAME}/lib/Text/Autoformat.pm

# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

B_R_DEPENDS+=  		::textproc/p5-Text-Reform

CONFIGURE_STYLE=	perl

DOT_FILES=		${FILESDIR}/dot.emacs ${FILESDIR}/dot.vimrc
SAMPLE_DIR=		${PREFIX}/share/examples/p5-Text-Autoformat

post-install:
			${INSTALL_DATA_DIR} ${SAMPLE_DIR}
			${INSTALL_DATA} ${DOT_FILES} ${SAMPLE_DIR}

.include <bsd.port.mk>
