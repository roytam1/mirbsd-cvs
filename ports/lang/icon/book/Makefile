# $OpenBSD: Makefile,v 1.2 2004/02/02 18:02:22 sturm Exp $

CATEGORIES=	books lang
COMMENT=			Icon programming language reference book

MASTER_SITES=	http://www.cs.arizona.edu/icon/ftp/doc/


# This documents version 9.3 of the language.
VSN=			9.3
DISTNAME=		icon-book-${VSN}

FLAVOURS=two_sided
FLAVOUR?=
.if ${FLAVOUR:L} == "two_sided"
DISTFILES=	lb2up.pdf
FULLPKGNAME=	icon-book-two_sided-${VSN}-${DASH_VER}
.else
DISTFILES=	lb1up.pdf
FULLPKGNAME=	icon-book-${VSN}-${DASH_VER}
.endif

SUPDISTFILES=	lb1up.pdf lb2up.pdf

# Book says:
# 'This book originally was published by Peer-to-Peer Communications.
# It is out of print and the rights have reverted to the authors, who hereby
# place it in the public domain'.
PERMIT_PACKAGE_FTP=Yes
PERMIT_PACKAGE_CDROM=Yes
PERMIT_DISTFILES_FTP=Yes
PERMIT_DISTFILES_CDROM=Yes

EXTRACT_ONLY=
NO_BUILD=Yes
PKG_ARCH=*

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/icon
	${INSTALL_DATA} ${FULLDISTDIR}/${DISTFILES} ${PREFIX}/share/doc/icon/icon-book${FLAVOUR_EXT}.pdf

.include <bsd.port.mk>
