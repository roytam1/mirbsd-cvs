# $MirOS: ports/x11/xloadimage/Makefile,v 1.8 2006/10/01 03:31:48 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/05/18 08:45:33 xsa Exp $

COMMENT=		graphics file viewer for X11
VERSION=		4.1
REVISION=		16	# Debian
DASH_VER=		2
DISTNAME=		xloadimage.${VERSION}
PKGNAME=		xloadimage-${VERSION}.${REVISION}-${DASH_VER}
CATEGORIES=		x11 graphics

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_R5CONTRIB}
MASTER_SITES0=	ftp://ftp.de.debian.org/debian/pool/main/x/xloadimage/ \
		ftp://ftp.debian.org/debian/pool/main/x/xloadimage/

PATCHFILES=		xloadimage_${VERSION}-${REVISION}.diff.gz:0
PATCH_DIST_STRIP=	-p1

LIB_DEPENDS+=		jpeg::graphics/jpeg \
			tiff::graphics/tiff
MODULES+=		graphics/png

USE_X11=		Yes
CONFIGURE_STYLE=	gnu
NO_REGRESS=		Yes

post-distpatch:
	@for p in ${WRKDIST}/debian/patches/*.dpatch; do \
		${PATCH} ${PATCH_DIST_ARGS} <$$p; \
	done

post-patch:
	@chmod a+rx ${WRKSRC}/configure

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/xloadimage ${PREFIX}/bin
	@cd ${PREFIX}/bin && \
	    ln -sf xloadimage xsetbg && \
	    ln -sf xloadimage xview
	${INSTALL_PROGRAM} ${WRKBUILD}/uufilter ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/xloadimage.man ${PREFIX}/man/man1/xloadimage.1
	@perl -i -pe 's:%%SYSCONFDIR%%:${SYSCONFDIR}:' \
	    ${PREFIX}/man/man1/xloadimage.1
	@cd ${PREFIX}/man/man1 && \
	    ln -sf xloadimage.1 xsetbg.1 && \
	    ln -sf xloadimage.1 xview.1
	${INSTALL_MAN} ${WRKSRC}/uufilter.man ${PREFIX}/man/man1/uufilter.1
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/xloadimage
	${INSTALL_DATA} ${WRKSRC}/xloadimagerc \
	    ${PREFIX}/share/examples/xloadimage/xloadimagerc

.include <bsd.port.mk>
