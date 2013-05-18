# $MirOS: ports/mailnews/fetchmail/Makefile,v 1.3 2006/02/09 09:36:01 tg Exp $
# $OpenBSD: Makefile,v 1.104 2005/10/27 21:58:51 bernd Exp $

COMMENT=			mail retrieval utility for POP2, POP3, IMAP, and more

DISTNAME=		fetchmail-6.2.5.2
CATEGORIES=		mail
MASTER_SITES=		http://download.berlios.de/fetchmail/
HOMEPAGE=		http://fetchmail.berlios.de/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--disable-nls --enable-inet6 --with-ssl \
			--without-kerberos --enable-NTLM
.if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--with-kerberos5
.else
CONFIGURE_ARGS+=	--without-kerberos5
.endif

NO_REGRESS=		Yes

DOCS=	FAQ NOTES FEATURES README COPYING fetchmail-FAQ.html \
	fetchmail-features.html design-notes.html todo.html

pre-patch:
	@sed -e "s|@PREFIX@|${LOCALBASE}|" \
	  ${FILESDIR}/fetchmailconf > ${WRKDIR}/fetchmailconf
	@tbl ${WRKSRC}/fetchmail.man > ${WRKSRC}/fetchmail.tbl && \
	  cp -f ${WRKSRC}/fetchmail.tbl ${WRKSRC}/fetchmail.man

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/fetchmail
	@cd ${PREFIX}/man/man1 && ln -sf fetchmail.1 fetchmailconf.1
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/fetchmail
	${INSTALL_SCRIPT} ${WRKSRC}/fetchmailconf \
	  ${PREFIX}/libexec/fetchmailconf.bin
	${INSTALL_SCRIPT} ${WRKDIR}/fetchmailconf ${PREFIX}/bin

.include <bsd.port.mk>
