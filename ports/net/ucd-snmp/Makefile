# $MirOS: ports/net/ucd-snmp/Makefile,v 1.6 2008/05/02 13:31:16 tg Exp $
# $OpenBSD: Makefile,v 1.38 2003/04/22 15:15:57 danh Exp $

COMMENT=		extensible SNMP implementation
VERSION=		4.2.6
DASH_VER=		2
DISTNAME=		ucd-snmp-${VERSION}
CATEGORIES=     	net
MASTER_SITES=   	${MASTER_SITE_SOURCEFORGE:=net-snmp/}
HOMEPAGE=		http://net-snmp.sourceforge.net/

# various BSD-styles
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

CONFIGURE_STYLE=	autoconf no-autoheader dest
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--with-defaults \
			--with-logfile=/var/log/snmpd \
			--with-persistent-directory=/var/ucd-snmp \
			--with-openssl \
			--with-zlib \
			--with-libs=-ldes \
			--with-sys-contact='default@' \
			--with-sys-location='Default Location'
CONFIGURE_ENV+=		VERSION_INFO=42:6:0
NO_REGRESS=		Yes

SNMP_BIN=		encode_keychange snmpbulkget snmpbulkwalk snmpdelta \
			snmpdf snmpget snmpgetnext snmpnetstat snmpset \
			snmpstatus snmptable snmptest snmptranslate snmptrap \
			snmpusm snmpvacm snmpwalk
SNMP_SBIN=		snmpd snmptrapd

post-extract:
	cp ${FILESDIR}/openbsd3.h ${WRKSRC}/s/openbsd3.h
	cd ${WRKSRC}/s && ln -s openbsd3.h mirbsd.h

post-install:
	cd ${PREFIX}/bin && ${STRIP} ${SNMP_BIN}
	cd ${PREFIX}/sbin && ${STRIP} ${SNMP_SBIN}
	${INSTALL_DATA_DIR} ${PREFIX}/share/{doc,examples}/ucd-snmp
	cd ${WRKSRC} && ${INSTALL_DATA} README README.snmpv3 FAQ AGENT.txt \
	    ${PREFIX}/share/doc/ucd-snmp/
	${INSTALL_DATA} ${WRKSRC}/EXAMPLE.conf \
	    ${PREFIX}/share/examples/ucd-snmp/

.include <bsd.port.mk>
