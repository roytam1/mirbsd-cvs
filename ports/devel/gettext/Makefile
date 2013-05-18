# $MirOS: ports/devel/gettext/Makefile,v 1.3 2005/07/24 11:50:14 bsiegert Exp $
# $FreeBSD: Makefile,v 1.4 1998/11/18 15:09:35 vanilla Exp $
# $OpenBSD: Makefile,v 1.29 2004/01/31 21:41:56 brad Exp $

COMMENT=	"GNU gettext"
DISTNAME=	gettext-0.10.40
PKGNAME=	${DISTNAME}-2
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=gettext/}
HOMEPAGE=	http://www.gnu.org/software/gettext/
MODULES=	converters/libiconv

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --with-included-gettext
LDFLAGS+=		-L${WRKBUILD}/intl/.libs

post-extract:
	@rm -f ${WRKSRC}/doc/gettext.info*

post-install:
	${INSTALL_DATA} ${WRKSRC}/misc/po-mode.el \
		${PREFIX}/share/gettext/po-mode.el
	@cd ${PREFIX}/lib && \
		perl -pi -e s#'-L${WRKBUILD}/intl/.libs '#''#g \
			libintl.la

do-regress:
	@cd ${WRKBUILD}/tests && ${MAKE_PROGRAM} check-TESTS

.include <bsd.port.mk>
