# $MirOS: ports/x11/gentoo/Makefile,v 1.4 2006/09/14 00:15:14 tg Exp $
# $OpenBSD: Makefile,v 1.6 2002/09/09 16:22:10 pvalchev Exp $

COMMENT=		gtk+ graphical file manager

VERSION=		0.11.34
DISTNAME=		gentoo-${VERSION}
CATEGORIES=		x11	

HOMEPAGE=		http://www.obsession.se/gentoo/

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=gentoo/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS= 		gtk.1.2,gdk.1.2::x11/gtk+1 \
			glib.1::devel/glib1

CONFIGURE_STYLE=	gnu
USE_X11=		Yes
NO_REGRESS=		Yes

post-install:
	${INSTALL_MAN} ${WRKSRC}/docs/gentoo.1x ${PREFIX}/man/man1/gentoo.1
.for i in gentoorc gentoogtkrc
	${INSTALL_DATA} ${WRKSRC}/$i ${PREFIX}/share/gentoo
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gentoo
	@cd ${WRKSRC}/docs && \
		tar cf - . | (cd ${PREFIX}/share/doc/gentoo; tar xf -) && \
		rm -f ${PREFIX}/share/doc/gentoo/gentoo.1x

.include <bsd.port.mk>
