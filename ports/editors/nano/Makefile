# $MirOS: ports/editors/nano/Makefile,v 1.7 2010/03/31 22:42:35 gecko2 Exp $
# $OpenBSD: Makefile,v 1.36 2004/02/20 21:30:38 naddy Exp $

COMMENT=		Free Pico clone with some new features
RESPONSIBLE=		Andreas Gockel <miros@unixforge.de>
DISTNAME=		nano-2.2.3
CATEGORIES=		editors
HOMEPAGE=		http://www.nano-editor.org/
MASTER_SITES=		${HOMEPAGE}dist/v2.2/

# GPLv3
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		devel/libncursesw
CONFIGURE_STYLE=	autogen
AUTOMAKE_VERSION=	1.9
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-utf8 \
			--enable-extra \
			--enable-color \
			--enable-multibuffer \
			--enable-nanorc \
			--disable-nls

post-install:
	${INSTALL_DATA_DIR} \
	    ${PREFIX}/share/examples/nano \
	    ${PREFIX}/share/doc/nano/man-html/fr
	${INSTALL_DATA} \
	    ${WRKSRC}/doc/nanorc.sample ${PREFIX}/share/examples/nano/
	cd ${WRKSRC:Q} && ${INSTALL_DATA} \
	    ABOUT-NLS AUTHORS BUGS COPYING COPYING.DOC ChangeLog \
	    ChangeLog.pre-2.1 INSTALL NEWS README README.SVN THANKS TODO \
	    UPGRADE doc/faq.html doc/texinfo/nano.html \
	    ${PREFIX}/share/doc/nano/
	cd ${WRKSRC:Q}/doc/man && ${INSTALL_DATA} \
	    nano.1.html nanorc.5.html rnano.1.html \
	    ${PREFIX}/share/doc/nano/man-html/
	cd ${WRKSRC:Q} && ${INSTALL_DATA} \
	    doc/man/fr/nano.1.html doc/man/fr/rnano.1.html \
	    doc/man/fr/nanorc.5.html ${PREFIX}/share/doc/nano/man-html/fr/
	-rm -rf ${PREFIX}/share/nano/man-html

.include <bsd.port.mk>
