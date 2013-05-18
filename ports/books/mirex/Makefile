# $MirOS: ports/books/mirex/Makefile,v 1.3 2005/08/21 11:48:20 tg Exp $

COMMENT=		"MirOS sample files, keys and information"
CATEGORIES=		books
CVS_DISTREPO=		_anoncvs@thor.66h.42h.de:/cvs
CVS_DISTDATE=		2005/12/18
CVS_DISTMODS=		contrib/samples
CVS_DISTFILE=		mirex
PKGNAME=		${_CVS_DISTF:R}-0
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://MirBSD.org/

# MirOS licence
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mirex

.include <bsd.port.mk>
