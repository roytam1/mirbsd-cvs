# $MirOS: ports/net/bitlbee/Makefile,v 1.6 2008/10/04 19:03:20 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/02/01 07:12:39 pvalchev Exp $

COMMENT=			IRC proxy to connect to ICQ, AOL, MSN and Jabber
DISTNAME=		bitlbee-1.0
CATEGORIES=		net
HOMEPAGE=		http://bitlbee.org

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://get.bitlbee.org/src/

DB_DIR?=		/var/bitlbee
ETCDIR=			${SYSCONFDIR}/bitlbee
EXAMPLEDIR=		${PREFIX}/share/examples/bitlbee
DOCS=			${FILESDIR}/user-guide.html
DOCDIR=			${PREFIX}/share/doc/bitlbee/
BITLBEEUSER=		_bitlbee
BITLBEEGROUP=		_bitlbee
ID=			509
SUBST_VARS=		DB_DIR ETCDIR EXAMPLEDIR DOCDIR \
			BITLBEEUSER BITLBEEGROUP ID

LIB_DEPENDS=		soup::devel/soup \
			glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib

CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=	--bindir=${PREFIX}/libexec \
			--mandir=${PREFIX}/man \
			--config=${DB_DIR} \
			--etcdir=${ETCDIR} \
			--prefix=${PREFIX} \
			--tcpd=0 \
			--ssl=openssl

USE_GMAKE=		Yes
MAKE_ENV=		CC=${_PASS_CC:Q}
FAKE_FLAGS=		${DESTDIRNAME}=${WRKINST} ETCDIR=${EXAMPLEDIR}
FAKE_TARGET=		install install-etc

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_DATA} ${DOCS} ${DOCDIR}

.include <bsd.port.mk>
