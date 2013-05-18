# $MirOS: ports/print/auctex/Makefile,v 1.3 2006/09/14 00:12:37 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/02/21 01:41:12 pvalchev Exp $

COMMENT=	extensible emacs interface for TeX

DISTNAME=	auctex-11.14
CATEGORIES=	print

HOMEPAGE=	http://www.gnu.org/software/auctex/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_GNU:=auctex/11.14/}

FAKE_FLAGS=	lispdir=${DESTDIR}/${PREFIX}/share/emacs/site-lisp
USE_CXX=	Yes # dependencies use CXX
USE_X11=	Yes # depends on t1lib, which needs X11

BUILD_DEPENDS=	:emacs-21.*:editors/emacs
RUN_DEPENDS=	${BUILD_DEPENDS} \
		:teTeX_base-*:print/teTeX/base

.include <bsd.port.mk>
