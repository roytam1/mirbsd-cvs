# $MirOS: ports/print/cups/Makefile,v 1.3 2005/12/16 01:07:12 bsiegert Exp $

COMMENT=		"Common Unix Printing System"

VERSION=		1.1.23
DASH_VER=		-1
DISTNAME=		cups-${VERSION}-source
PKGNAME=		${DISTNAME:S/-source//}${DASH_VER}
CATEGORIES=		print sysutils

HOMEPAGE=		http://www.cups.org/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		ftp://ftp.easysw.com/pub/cups/${VERSION}/ \
			ftp://ftp2.easysw.com/pub/cups/${VERSION}/
			
EXTRACT_SUFX=		.tar.bz2

LIB_DEPENDS=		jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff
MODULES+=		graphics/png

FAKE_FLAGS+=		BINMODE=${BINMODE} \
			SHAREMODE=${SHAREMODE} \
			top_builddir=${WRKBUILD}
MAKE_FLAGS+=		top_builddir=${WRKBUILD}

CONFIGURE_STYLE=	autoconf no-autoheader dest
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-cups-user=_cups \
			--with-cups-group=_cups \
			${CONFIGURE_SHARED} \
			--localstatedir=/var \
			--enable-ssl

CONFIGURE_ENV=		DSOFLAGS="-L${LOCALBASE}/lib"

WRKDIST=		${WRKDIR}/${DISTNAME:S/-source//}

REGRESS_FLAGS=		LOCALBASE=${LOCALBASE}

REGRESS_DEPENDS=	::print/htmldoc
REGRESS_IS_INTERACTIVE=	Yes

USE_CXX=		yes

post-configure:
.for i in cups.sh config.h cups-config conf/cupsd.conf
	@mv ${WRKBUILD}/${i} ${WRKBUILD}/${i}.bak
	@sed -e s#\$${DESTDIR}##g ${WRKBUILD}/${i}.bak > ${WRKBUILD}/${i}
.endfor

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/examples/cups
	@cd ${WRKINST}/etc/cups && cp -Rp * ${PREFIX}/share/examples/cups
	@${INSTALL_DATA} ${WRKBUILD}/cups.sh ${PREFIX}/share/cups
	@${INSTALL_DATA} ${FILESDIR}/README.MirBSD ${PREFIX}/share/doc/cups
.for file in cups-enable cups-disable
	@sed s,y0y0y0,${TRUEPREFIX}, < ${FILESDIR}/${file} > \
		${PREFIX}/sbin/${file}
	@chmod ${BINMODE} ${PREFIX}/sbin/${file}
	@chown ${BINOWN}:${BINGRP} ${PREFIX}/sbin/${file}
.endfor

.include <bsd.port.mk>
