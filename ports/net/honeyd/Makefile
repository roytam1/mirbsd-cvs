# $MirOS: ports/net/honeyd/Makefile,v 1.2 2005/04/10 21:50:38 tg Exp $
# $OpenBSD: Makefile,v 1.6 2003/12/31 08:44:49 pvalchev Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}
COMMENT=			utility to create virtual hosts on a network
DISTNAME=	honeyd-0.7a
CATEGORIES=	net
MASTER_SITES=	${HOMEPAGE} \
		http://niels.xtdnet.nl/honeyd/
HOMEPAGE=	http://www.citi.umich.edu/u/provos/honeyd/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

BUILD_DEPENDS=	${LOCALBASE}/lib/libdnet.a::net/libdnet

CONFIGURE_STYLE=autoconf automake
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS+=--without-python

SCRIPTS=	proxy.pl router-telnet.pl smtp.pl test.sh web.sh
SCRIPTS-snmp=	README buildSNMPConfig.pl default.snmp fake-snmp.pl \
		linux-2.4.snmp.tpl windows2000.snmp.tpl

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/honeyd/scripts/snmp
.for f in ${SCRIPTS}
	${INSTALL_SCRIPT} ${WRKSRC}/scripts/${f} ${PREFIX}/share/honeyd/scripts
.endfor
.for f in ${SCRIPTS-snmp}
	${INSTALL_SCRIPT} ${WRKSRC}/scripts/snmp/${f} \
		${PREFIX}/share/honeyd/scripts/snmp
.endfor

.include <bsd.port.mk>
