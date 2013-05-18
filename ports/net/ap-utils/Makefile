# $MirOS: ports/net/ap-utils/Makefile,v 1.2 2006/02/02 21:09:40 tg Exp $
# $OpenBSD: Makefile,v 1.2 2003/06/02 02:02:35 margarida Exp $

COMMENT=			wireless access point configuration tools
DISTNAME=	ap-utils-1.3.2
CATEGORIES=	net
EXTRACT_SUFX=	.tar.bz2
HOMEPAGE=	http://ap-utils.polesye.net/
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=ap-utils/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		devel/gettext

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--without-included-gettext \
			--with-libiconv-prefix=${ICONV_PREFIX} \
			--with-libintl-prefix=${LOCALBASE}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/systrace/
	${INSTALL_DATA} files/bin_ap_config ${PREFIX}/share/examples/systrace/

.include <bsd.port.mk>
