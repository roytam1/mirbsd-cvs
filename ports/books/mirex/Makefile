# $MirOS: ports/books/mirex/Makefile,v 1.4 2005/12/18 16:36:26 tg Exp $

BROKEN=being updated

COMMENT=		"MirOS sample files, keys and information"
CATEGORIES=		books
CVS_DISTREPO=		_anoncvs@anoncvs.66h.42h.de:/cvs
CVS_DISTDATE=		2006/01/27
CVS_DISTMODS=		contrib/samples src/share/doc/README
#	XXX da wollen wir mal was tun ;)
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
