# $MirOS$
# $OpenBSD: Makefile,v 1.14 2003/11/15 15:12:55 sturm Exp $

COMMENT=	generate groff/HTML from linuxdoc/docbook SGML documents

DISTNAME=	sgmlformat-1.7
CATEGORIES=	textproc print
MASTER_SITES=	http://fallout.campusview.indiana.edu/ports/distfiles/


# License: BSD, badly worded
PERMIT_PACKAGE_CDROM=	dependency textproc/linuxdoc is not allowed for CDROM
PERMIT_PACKAGE_FTP=	dependency textproc/linuxdoc is not allowed for FTP
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

RUN_DEPENDS=	::textproc/openjade \
		::textproc/linuxdoc \
		::textproc/docbook

FAKE_FLAGS=PREFIX=${PREFIX}

.include <bsd.port.mk>
