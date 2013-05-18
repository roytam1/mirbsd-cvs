# $MirOS: ports/print/foomatic/filters/Makefile,v 1.3 2006/09/14 00:12:40 tg Exp $

COMMENT=		universal print filter script

VERSION=		3.0.2
DISTNAME=		foomatic-filters-${VERSION}
DASH_VER=		1
CATEGORIES=		print

HOMEPAGE=		http://www.linuxprinting.org/foomatic.html
MASTER_SITES=		http://www.linuxprinting.org/download/foomatic/

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= 	gnu

B_R_DEPENDS+=		::print/a2ps
B_R_DEPENDS+=		::print/cups

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/foomatic
	${INSTALL_DATA_DIR} ${PREFIX}/libexec/cups/filter
	${INSTALL_DATA} ${WRKSRC}/filter.conf ${PREFIX}/share/examples/foomatic
.for i in foomatic-rip foomatic-gswrapper
	${INSTALL_SCRIPT} ${WRKSRC}/$i ${PREFIX}/bin
	${INSTALL_DATA} ${WRKSRC}/$i.1 ${PREFIX}/man/man1
.endfor
	cd ${PREFIX}/libexec/cups/filter ; ln -s ${PREFIX}/bin/foomatic-rip . || cp ${PREFIX}/bin/foomatic-rip .

.include <bsd.port.mk>
