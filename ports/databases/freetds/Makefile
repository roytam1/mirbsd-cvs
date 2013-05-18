# $MirOS: ports/databases/freetds/Makefile,v 1.2 2006/02/02 21:09:40 tg Exp $
# $OpenBSD: Makefile,v 1.17 2004/04/14 03:17:04 jcs Exp $

COMMENT=			project to document and implement the TDS protocol
DISTNAME=	freetds-0.62.4
CATEGORIES=	databases
HOMEPAGE=	http://www.freetds.org/
MASTER_SITES=	http://ibiblio.org/pub/Linux/ALPHA/freetds/stable/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		${CONFIGURE_SHARED} \
			--enable-static \
			--with-libiconv-prefix="${ICONV_PREFIX}" \
			--disable-threadsafe \
			--disable-odbc
MAKE_ENV=		RM=rm
MODULES=		devel/gettext

post-install:
	@sed -e "s:@sysconfdir@:${SYSCONFDIR}:g" ${WRKSRC}/freetds.conf \
	    >${WRKSRC}/freetds.conf.new
	@mkdir ${PREFIX}/share/examples/freetds
	${INSTALL_DATA} ${WRKSRC}/freetds.conf.new \
		${PREFIX}/share/examples/freetds/freetds.conf-sample
	${INSTALL_DATA} ${WRKSRC}/src/pool/pool.conf \
		${PREFIX}/share/examples/freetds/pool.conf-sample

.include <bsd.port.mk>
