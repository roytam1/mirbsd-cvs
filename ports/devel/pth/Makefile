# $MirOS: ports/devel/pth/Makefile,v 1.1.7.1 2005/03/18 15:45:22 tg Exp $
# $OpenBSD: Makefile,v 1.11 2002/12/29 20:19:12 fgsch Exp $

COMMENT=			GNU portable threads
DISTNAME=	pth-1.4.1
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=pth/}
HOMEPAGE=	http://www.gnu.org/software/pth/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static \
		 --enable-syscall-soft \
		 --enable-optimize \
		 --enable-batch

REGRESS_TARGET=	test

.include <bsd.port.mk>
