# $MirOS$
# $OpenBSD: Makefile,v 1.7 2004/01/27 20:19:13 sturm Exp $

COMMENT=	"audio file volume normalizer"

DISTNAME=	normalize-0.7.4
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio
MASTER_SITES=	http://www.cs.columbia.edu/~cvaill/normalize/

HOMEPAGE=	http://www.cs.columbia.edu/~cvaill/normalize/


# GPL license
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.if ${MACHINE_ARCH} == "sparc64"
PATCH_LIST=	patch-* gcc-*
.endif

MODULES=	devel/gettext

CONFIGURE_STYLE=gnu

# Do not build xmms plugin for now.
CONFIGURE_ARGS=	--disable-xmms \
		--with-mad \
		--with-audiofile

LIB_DEPENDS=	mad::audio/libmad \
		audiofile::devel/libaudiofile

.include <bsd.port.mk>
