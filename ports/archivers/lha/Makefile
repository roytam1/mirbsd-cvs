# $MirOS: ports/archivers/lha/Makefile,v 1.2 2005/07/07 21:16:55 bsiegert Exp $
# $OpenBSD: Makefile,v 1.23 2004/05/06 23:07:57 naddy Exp $

COMMENT=	"archive files using LZW compression (.lzh files)"

VERSION=	1.14i
DISTNAME=	lha-${VERSION:S/.//}
PKGNAME=	lha-${VERSION}-1
CATEGORIES=	archivers

HOMEPAGE=       http://www2m.biglobe.ne.jp/~dolphin/lha/lha.htm


# Restrictive
PERMIT_PACKAGE_CDROM=	"requires advance notification"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"requires advance notification"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www2m.biglobe.ne.jp/~dolphin/lha/prog/ \
		ftp://ftp.win.ne.jp/pub/misc/

EXTRA_MAKE_FLAGS=	OPTIMIZE="${CFLAGS}" \
			MACHINE="-DSYSTIME_HAS_NO_TM -DSYSV_SYSTEM_DIR \
			    -DMKTIME -DUSESTRCASECMP" \
			SWITCHES="-DNEED_INCREMENTAL_INDICATOR -DEUC \
			    -DSUPPORT_LH7"

EXTRA_FAKE_FLAGS=	BINDIR="${WRKINST}${PREFIX}/bin" \
			MANDIR="${WRKINST}${PREFIX}/man/ja_JP.EUC" MANSECT="1" \
			INSTALL="" INSTALLBIN="${INSTALL_PROGRAM}" \
			INSTALLMAN="${INSTALL_MAN}"

NO_REGRESS=	Yes

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/man/ja_JP.EUC/man1

.include <bsd.port.mk>
