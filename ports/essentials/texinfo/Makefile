# $MirOS$

COMMENT=		"GNU's man page successor"
DISTNAME=		texinfo-4.8
CATEGORIES=		textproc
MASTER_SITES=		${MASTER_SITE_GNU:=texinfo/}
HOMEPAGE=		http://www.gnu.org/software/texinfo/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--disable-nls
NO_REGRESS=		Yes

.include <bsd.port.mk>
