# $MirOS: ports/japanese/canna/Makefile,v 1.2 2005/07/07 21:22:09 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2003/03/12 21:21:54 brad Exp $

COMMENT=			canna (kana-kanji converter) libraries
COMMENT-dict=			canna (kana-kanji converter) dictionaries
COMMENT-server=			canna (kana-kanji converter) server

CATEGORIES=	japanese
DISTNAME=	Canna35b2
HOMEPAGE=	http://www.nec.co.jp/japanese/product/computer/soft/canna/

PKGNAME=	cannalib-3.5b2p1-0
PKGNAME-dict=	cannadict-3.5b2-0
PKGNAME-server=	cannaserver-3.5b2p1-0

MASTER_SITES=	ftp://ftp.nec.co.jp/pub/Canna/Canna35/
MASTER_SITES0=	http://www.jaist.ac.jp/~fujieda/canna/
PATCHFILES=	Canna35b2-unoff1.patch.gz:0 Canna35b2-unoff2.patch.gz:0 \
		Canna35b2-hack1.patch.gz:0
PATCH_DIST_STRIP=	-p1

# 4-clause BSD-style, differently worded
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MULTI_PACKAGES=		-dict -server

.if defined(PACKAGING) 
SUBPACKAGE?=
.  if ${SUBPACKAGE}=="-dict"
PREFIX=			/var/dict
.  endif
.endif

SUBST_VARS+=		DICT_DIR
CONFIGURE_STYLE=	imake
CANNAOWNER=		daemon
CANNAGROUP=		daemon
DICT_DIR=		/var/dict/canna
MAKE_ENV+=		CANNAOWNER=${CANNAOWNER} CANNAGROUP=${CANNAGROUP} \
			DICT_DIR=${DICT_DIR} CANNA_SPOOL=/var/spool/canna

USE_X11=		Yes
DIFF_ARGS=		-u2
NO_REGRESS=		Yes

.include <bsd.port.mk>
