# $MirOS: ports/devel/gettext/Makefile,v 1.5 2006/09/14 00:08:11 tg Exp $
# $FreeBSD: Makefile,v 1.4 1998/11/18 15:09:35 vanilla Exp $
# $OpenBSD: Makefile,v 1.29 2004/01/31 21:41:56 brad Exp $

COMMENT=		GNU gettext
DISTNAME=		gettext-0.10.40
DASH_VER=		2
CATEGORIES=		devel
MASTER_SITES=		${MASTER_SITE_GNU:=gettext/}
HOMEPAGE=		http://www.gnu.org/software/gettext/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=		converters/libiconv
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--disable-libtool-lock \
			--with-included-gettext

post-extract:
	@rm -f ${WRKSRC}/doc/gettext.info*

post-install:
	${INSTALL_DATA} ${WRKSRC}/misc/po-mode.el \
		${PREFIX}/share/gettext/po-mode.el

do-regress:
	@cd ${WRKBUILD}/tests && ${MAKE_PROGRAM} check-TESTS

.include <bsd.port.mk>
