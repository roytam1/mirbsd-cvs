# $MirOS$

COMMENT=		GNU version of the stream editor
VERSION=		4.1.5
DISTNAME=		sed-${VERSION}
PKGNAME=		gsed-${VERSION}
CATEGORIES=		textproc
HOMEPAGE=		http://www.gnu.org/software/sed/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=sed/}

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--program-prefix=g \
			--disable-dependency-tracking \
			--disable-nls
EXTRA_FAKE_FLAGS+=	mkinstalldirs='mkdir -p'

post-extract:
	-rm -f ${WRKSRC}/doc/*.info*

.include <bsd.port.mk>
