# $MirOS$
# $OpenBSD: Makefile,v 1.28 2002/12/14 14:09:07 naddy Exp $

COMMENT=	format ascii files for printing on PostScript printers

DISTNAME=	a2ps-4.13b
DASH_VER=	1
PKGNAME=	a2ps-4.13.2-${DASH_VER}
WRKDIST=	${WRKDIR}/a2ps-4.13
CATEGORIES=	print

# License info.  There is some questionable Sun and
# Adobe Copyrighted things in this source tree.  It
# looks fine for FTP, but likely not for the CDROM.
PERMIT_PACKAGE_CDROM=	"No fee redistribution."
PERMIT_DISTFILES_CDROM=	"No fee redistribution."
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.enst.fr/pub/unix/a2ps/

USE_ICONV=		any oldm4
MODULES=		devel/gettext

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
USE_GMAKE=		Yes
AUTOGEN=		${SHELL} ${FILESDIR}/autogen.sh

PAPERSIZE=	A4
CONFIGURE_ARGS=	--with-medium=${PAPERSIZE} \
		${CONFIGURE_SHARED}

post-extract:
.for i in c-bs-a.m4 ccstdc.m4 cond.m4 depend.m4 gettext.m4 header.m4 init.m4 lcmessage.m4 lex.m4 libtool.m4 lispdir.m4 missing.m4 progtest.m4 protos.m4 sanity.m4 termios.m4 winsz.m4
	rm -f ${WRKSRC}/m4/${i}
.endfor

pre-build:
	/usr/bin/touch $(WRKSRC)/doc/*.info
	/usr/bin/touch $(WRKSRC)/doc/*.dvi

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/a2ps/etc
	${INSTALL_DATA} ${WRKSRC}/etc/a2ps.cfg ${PREFIX}/share/a2ps/etc
	${INSTALL_DATA} ${WRKSRC}/etc/a2ps-site.cfg ${PREFIX}/share/a2ps/etc

.include <bsd.port.mk>
