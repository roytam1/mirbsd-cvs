# $MirOS: ports/mailnews/fetchmail/Makefile,v 1.4 2006/09/14 00:10:34 tg Exp $
# $OpenBSD: Makefile,v 1.104 2005/10/27 21:58:51 bernd Exp $

COMMENT=		mail retrieval utility for POP2, POP3, IMAP, and more
DISTNAME=		fetchmail-6.3.4
CATEGORIES=		mail
MASTER_SITES=		http://download.berlios.de/fetchmail/ \
			http://download2.berlios.de/fetchmail/
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://fetchmail.berlios.de/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-dependency-tracking \
			--disable-nls \
			--enable-NTLM \
			--without-kerberos \
			--with-ssl
.if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--with-kerberos5
.else
CONFIGURE_ARGS+=	--without-kerberos5
.endif
CONFIGURE_ENV+=		am_cv_pathless_PYTHON=none

NO_REGRESS=		Yes

DOCS=			COPYING FAQ FEATURES NEWS NOTES OLDNEWS README \
			README.SSL TODO design-notes.html \
			esrs-design-notes.html fetchmail-FAQ.html \
			fetchmail-FAQ.pdf fetchmail-features.html

post-build:
	sed -e 's#@PREFIX@#${LOCALBASE}#g' <${FILESDIR}/fetchmailconf \
	    >${WRKBUILD}/fetchmailconf

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/fetchmail
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/fetchmail/
	cd ${PREFIX}/man/man1 && \
	    mv fetchmail.1 fetchmail.tbl && \
	    ln -s fetchmail.tbl fetchmailconf.tbl
	${INSTALL_SCRIPT} ${WRKBUILD}/fetchmailconf ${PREFIX}/bin/
	${INSTALL_SCRIPT} ${WRKSRC}/fetchmailconf.py ${PREFIX}/libexec/

.include <bsd.port.mk>
