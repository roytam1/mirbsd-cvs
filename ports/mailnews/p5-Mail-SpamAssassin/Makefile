# $MirOS: ports/mailnews/p5-Mail-SpamAssassin/Makefile,v 1.4 2008/10/04 19:03:17 tg Exp $
# $OpenBSD: Makefile,v 1.29 2004/01/21 08:01:59 brad Exp $

COMMENT=			mailfilter to identify and mark spam

DISTNAME=		Mail-SpamAssassin-2.63
PKGNAME=		p5-${DISTNAME}-0
CATEGORIES=		mail perl5
HOMEPAGE=		http://spamassassin.org/

# Artistic License
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}released/ \
			${MASTER_SITE_PERL_CPAN:=Mail/}

BUILD_DEPENDS=		:p5-HTML-Parser-*:www/p5-HTML-Parser
RUN_DEPENDS=		:p5-Net-DNS-*:net/p5-Net-DNS \
			:p5-HTML-Parser-*:www/p5-HTML-Parser

MAKE_ENV+=		CC=${_PASS_CC:T:Q}

CONFIGURE_STYLE=	perl
INSTALL_TARGET=		LOCAL_RULES_DIR=${WRKINST}${SAMPLE_CONFIG_DIR} install
CONFIGURE_ARGS+=	RUN_RAZOR_TESTS="no" \
			SYSCONFDIR=${SYSCONFDIR} \
			CONTACT_ADDRESS="the administrator of that system"
CONFDIR=		${SYSCONFDIR}/mail/spamassassin
RULES_DIR=		${PREFIX}/share/spamassassin
SAMPLE_CONFDIR=		${PREFIX}/share/examples/SpamAssassin
SUBST_VARS=		CONFDIR SAMPLE_CONFDIR
FAKE_FLAGS=		${DESTDIRNAME}=${WRKINST} \
			PKG_DEF_RULES_DIR=${WRKINST}${RULES_DIR} \
			PKG_LOCAL_RULES_DIR=${WRKINST}${SAMPLE_CONFDIR}

# regress insists on creating files in $HOME
PORTHOME=		${WRKDIR}/temp-home

FAQS=	${FILESDIR}/OpenBSD-SpamAssassin-mini-howto.html
DOCS=	README procmailrc.example \
	sample-nonspam.txt sample-spam.txt

post-patch:
	@perl -pi -e "s#\@\@LOCAL_RULES_DIR\@\@#${CONFDIR}#" ${WRKSRC}/rules/*

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/SpamAssassin
	${INSTALL_DATA_DIR} ${SAMPLE_CONFDIR}
	${INSTALL_DATA} ${FAQS} ${PREFIX}/share/doc/SpamAssassin
	cd ${WRKSRC} && ${INSTALL_DATA} rules/local.cf ${SAMPLE_CONFDIR}
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/SpamAssassin
	cd ${WRKSRC} && pod2man --section=1 spamd/spamc.pod > \
	    ${PREFIX}/man/man1/spamc.1
	cd ${WRKSRC} && pod2man --section=8 spamd/spamd > \
	    ${PREFIX}/man/man8/spamd.8

pre-regress:
	mkdir -p ${PORTHOME}

.include <bsd.port.mk>
