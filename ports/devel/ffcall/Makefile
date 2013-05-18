# $MirOS: ports/devel/ffcall/Makefile,v 1.1.7.1 2005/03/18 15:44:33 tg Exp $
# $OpenBSD: Makefile,v 1.5 2003/07/06 22:46:14 pvalchev Exp $
# $FreeBSD: ports/devel/ffcall/Makefile,v 1.2 2001/08/31 14:20:18 sobomax Exp $
# Original From:                jagapen@home.com

IGNORE=		"might be broken, used to use Libtool"

COMMENT=			foreign function call libraries
DISTNAME=	ffcall-1.8
CATEGORIES=	devel
MASTER_SITES=	ftp://ftp.ilog.fr/pub/Users/haible/gnu/
HOMEPAGE=	http://www.haible.de/bruno/packages-ffcall.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= gnu
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC}/autoconf

FAKE_FLAGS=	${DESTDIRNAME}=${WRKINST} \
		LIBTOOL="${LIBTOOL} ${LIBTOOL_FLAGS}" \
		htmldir="\$$(datadir)/doc/ffcall/html"

pre-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ffcall/html

.include <bsd.port.mk>
