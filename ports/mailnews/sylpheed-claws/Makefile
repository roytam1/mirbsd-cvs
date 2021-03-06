# $MirOS: ports/mailnews/sylpheed-claws/Makefile,v 1.7 2007/04/12 20:24:59 bsiegert Exp $
# $OpenBSD: Makefile,v 1.5 2004/02/04 07:39:18 sturm Exp $

COMMENT=			lightweight GTK+ based mail/news client
COMMENT-dillo=			Dillo plugin for sylpheed-claws
COMMENT-imageviewer=		Image viewer plugin for sylpheed-claws
COMMENT-spamassassin=		Spamassassin plugin for sylpheed-claws
COMMENT-themes=			Sylpheed-claws themes

VERSION=		0.9.0
DASH_VER=		0
DISTNAME=		sylpheed-${VERSION}claws
PKGNAME=		sylpheed-claws-${VERSION}-${DASH_VER}
THEMEFILE=		sylpheed-iconset-20030523
CATEGORIES=		mail news x11

HOMEPAGE=		http://sylpheed-claws.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=sylpheed-claws/}
DISTFILES=		$(DISTNAME).tar.bz2 \
			$(THEMEFILE).tar.gz

MODULES=		devel/gettext
LIB_DEPENDS=		gdk.1,gtk.1::x11/gtk+1 \
			gthread.1::devel/glib1

USE_CXX=		Yes
USE_X11=		Yes
CONFIGURE_STYLE= 	gnu
CONFIGURE_ARGS=		--enable-ipv6 --enable-openssl \
			--program-suffix="-claws" \
			--enable-spamassassin-plugin \
			--enable-dillo-viewer-plugin

FLAVOURS=		compface gpgme jpilot ldap pixbuf
FLAVOUR?=

MULTI_PACKAGES=		-dillo -imageviewer -spamassassin -themes

# Need GNU/aspell >= 0.50
#.if ${FLAVOUR:L:Maspell}
#LIB_DEPENDS+=		aspell::textproc/aspell
#CONFIGURE_ARGS+=	--enable-aspell
#.endif

.if ${FLAVOUR:L:Mcompface}
PERMIT_PACKAGE_CDROM=   "No Fee"
PERMIT_DISTFILES_CDROM= "No Fee"
LIB_DEPENDS+=		compface.1::mailnews/faces
CONFIGURE_ARGS+=	--enable-compface
.else
CONFIGURE_ARGS+=	--disable-compface
.endif

.if ${FLAVOUR:L:Mgpgme}
LIB_DEPENDS+=		gpgme.4::security/gpgme
CONFIGURE_ARGS+=	--enable-gpgme
.endif

.if ${FLAVOUR:L:Mjpilot}
LIB_DEPENDS+=		pisock.4::comms/pilot-link
RUN_DEPENDS+=		:jpilot-*:comms/jpilot
CONFIGURE_ARGS+= 	--enable-jpilot
.endif

.if ${FLAVOUR:L:Mldap}
LIB_DEPENDS+=		ldap.2,lber.2:openldap-client-*:databases/openldap
CONFIGURE_ARGS+=	--enable-ldap
.endif

.if !${FLAVOUR:L:Mpixbuf}
LIB_DEPENDS+=		gdk_imlib.19::graphics/imlib
CONFIGURE_ARGS+=	--enable-imblib --disable-gdk-pixbuf
.else
LIB_DEPENDS+=		gdk_pixbuf.2::graphics/gdk-pixbuf
CONFIGURE_ARGS+=	--enable-gdk-pixbuf --disable-imlib
.endif

.for i in ${MULTI_PACKAGES}
FULLPKGNAME$i=		sylpheed-claws${i}-${VERSION}-${PL}
.endfor

SUBPACKAGE?=

.if defined(PACKAGING) && !empty(SUBPACKAGE)
RUN_DEPENDS=            ::mailnews/sylpheed-claws
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-themes"
PKG_ARCH=		*
.endif

.if ${SUBPACKAGE:M-spamassassin}
RUN_DEPENDS+=		:p5-Mail-SpamAssassin-*:mailnews/p5-Mail-SpamAssassin
.endif

.if ${SUBPACKAGE:M-dillo}
RUN_DEPENDS+=		:dillo-*:www/dillo
.endif

FILES=		OOo2sylpheed.pl calypso_convert.pl eud2gc.py \
		filter_conv.pl gif2xface.pl google_msgid.pl \
		gpg-sign-syl kmail2sylpheed.pl kmail2sylpheed_v2.pl \
		newscache_clean.pl outlook2sylpheed.pl \
		tb2sylpheed update-po uudec sylprint.pl sylprint.rc

THEMES=		Crystal mongrel tml02c Kovico-sylpheed XeNtish mozilla \
		New_Session black stw Plain_and_Bluish blue_anarchy sylzilla

DATADIR=	${PREFIX}/share/sylpheed-claws
DOCSDIR=	${PREFIX}/share/doc/sylpheed-claws

post-patch:
	@cd ${WRKSRC} && mv sylpheed.png sylpheed-claws.png && \
		mv sylpheed.desktop sylpheed-claws.desktop
	@perl -pi -e 's|pheed|pheed-claws|g' ${WRKSRC}/sylpheed-claws.desktop
	@perl -pi -e 's|%%PREFIX%%|${PREFIX}|g' \
		${WRKSRC}/tools/sylpheed-switcher

post-install:
	${INSTALL_DATA_DIR} ${DATADIR}/themes
.for d in ${THEMES}
	@cp -R ${WRKDIR}/${THEMEFILE}/$d ${DATADIR}/themes/
.endfor
	@find ${DATADIR}/themes -type d -print0 | xargs -0 chmod 755
	@find ${DATADIR}/themes -type f -print0 | xargs -0 chmod 444
	${INSTALL_SCRIPT} ${WRKSRC}/tools/sylpheed-switcher ${PREFIX}/bin/
.for f in ${FILES}
	${INSTALL_DATA} ${WRKSRC}/tools/$f ${DATADIR}/$f
.endfor
	${INSTALL_DATA} ${WRKSRC}/tools/README ${DOCSDIR}/README.tools
	${INSTALL_DATA} ${WRKSRC}/tools/README.sylprint ${DOCSDIR}/
	${INSTALL_DATA} ${WRKDIR}/${THEMEFILE}/README ${DOCSDIR}/README.themes
	${INSTALL_DATA} ${WRKSRC}/src/plugins/dillo_viewer/README \
		${DOCSDIR}/README.dillo
	${INSTALL_DATA} ${WRKSRC}/src/plugins/spamassassin/README \
		${DOCSDIR}/README.spamassassin
.for f in AUTHORS README README.claws README.jp RELEASE_NOTES.claws 
	${INSTALL_DATA} ${WRKSRC}/$f ${DOCSDIR}/$f
.endfor

.include <bsd.port.mk>
