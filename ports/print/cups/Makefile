# $MirOS: ports/print/cups/Makefile,v 1.18 2007/12/21 23:37:08 bsiegert Exp $

COMMENT=		Common Unix Printing System

VERSION=		1.3.9
DASH_VER=		0
DISTNAME=		cups-${VERSION}-source
PKGNAME=		${DISTNAME:S/-source//}-${DASH_VER}
CATEGORIES=		print sysutils

HOMEPAGE=		http://www.cups.org/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES+=		ftp://ftp.easysw.com/pub/cups/${VERSION}/
MASTER_SITES+=		ftp://ftp2.easysw.com/pub/cups/${VERSION}/
MASTER_SITES+=		${MASTER_SITE_SOURCEFORGE:=cups/}
			
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS+=		jpeg::graphics/jpeg
LIB_DEPENDS+=		tiff::graphics/tiff
LIB_DEPENDS+=		ldap,lber::databases/openldap
LIB_DEPENDS+=		dbus-1::sysutils/dbus
MODULES+=		graphics/png

EXTRA_XAKE_FLAGS+=	BINMODE=${BINMODE} \
			SHAREMODE=${SHAREMODE}

CONFIGURE_STYLE=	autoconf no-autoheader dest
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-cups-user=_cups \
			--with-cups-group=_cups \
			${CONFIGURE_SHARED} \
			--localstatedir=${PREFIX}/var \
			--with-cachedir=\${DESTDIR}${PREFIX}/var/cache/cups \
			--without-php \
			--enable-ssl

CONFIGURE_ENV=		DSOFLAGS="-L${LOCALBASE}/lib"
#COPTS+=			-idirafter ${WRKSRC}

WRKDIST=		${WRKDIR}/${DISTNAME:S/-source//}

LDFLAGS+=		-pthread
REGRESS_FLAGS=		LOCALBASE=${LOCALBASE}

REGRESS_DEPENDS=	::print/htmldoc
REGRESS_IS_INTERACTIVE=	Yes

USE_CXX=		yes

pre-patch:
	@echo 'include(libtool.m4)' >> ${WRKSRC}/aclocal.m4

post-configure:
.for i in config.h cups-config conf/cupsd.conf
	@mv ${WRKBUILD}/${i} ${WRKBUILD}/${i}.bak
	@sed -e s#\$${DESTDIR}##g ${WRKBUILD}/${i}.bak > ${WRKBUILD}/${i}
.endfor

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/cups
	@cd ${WRKINST}${SYSCONFDIR}/cups && cp -Rp * ${PREFIX}/share/examples/cups
	${INSTALL_DATA} ${WRKSRC}/packaging/cups-dbus.conf ${PREFIX}/share/examples/cups
	@${INSTALL_DATA} ${WRKBUILD}/init/cups.sh ${PREFIX}/share/cups
	@${INSTALL_DATA} ${FILESDIR}/README.MirBSD ${PREFIX}/share/doc/cups
.for file in cups-enable cups-disable
	@sed s,y0y0y0,${TRUEPREFIX}, < ${FILESDIR}/${file} > \
		${PREFIX}/sbin/${file}
	@chmod ${BINMODE} ${PREFIX}/sbin/${file}
	@chown ${BINOWN}:${BINGRP} ${PREFIX}/sbin/${file}
.endfor

.include <bsd.port.mk>
