# $MirOS$
# $OpenBSD: Makefile,v 1.7 2004/02/20 23:51:29 pvalchev Exp $

COMMENT=	"programmable small perl irc client (utf-8, IPv6)"
CATEGORIES=	net
DISTNAME=	sirc-2.211
PKGNAME=	${DISTNAME}p11
MASTER_SITES=	http://www.iagora.com/~espel/sirc/
RESPONSIBLE=	Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>
HOMEPAGE=	http://www.iagora.com/~espel/sirc/sirc.html

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

RUN_DEPENDS=		:p5-Socket6->=0.08:net/p5-Socket6

post-extract:
	@cp ${FILESDIR}/Makefile ${WRKSRC}/

pre-patch:
	@gzip -d ${WRKSRC}/sirc.help.gz

post-patch:
	@sed s!PREFIX.SED!${PREFIX}!g ${FILESDIR}/sirc-script >${WRKSRC}/sirc
	@sed s!PREFIX.SED!${PREFIX}!g ${WRKSRC}/dsirc >${WRKSRC}/dsircp

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/ssfe ${PREFIX}/bin/
	${INSTALL_SCRIPT} ${WRKSRC}/sirc ${WRKSRC}/dsircp \
	    ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKSRC}/sirc.1 ${WRKSRC}/ssfe.1 \
	    ${PREFIX}/man/man1/
	${INSTALL_DATA_DIR} ${PREFIX}/share/sirc
	${INSTALL_DATA} ${WRKSRC}/sirc.help ${WRKSRC}/PROGRAMMING \
	    ${WRKSRC}/README ${WRKSRC}/README.socks ${WRKSRC}/n0thing.pl \
	    ${PREFIX}/share/sirc/

.include <bsd.port.mk>
