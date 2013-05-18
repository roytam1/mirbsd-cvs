# $MirOS: ports/archivers/lha/Makefile,v 1.4 2006/09/14 00:06:48 tg Exp $
# $OpenBSD: Makefile,v 1.23 2004/05/06 23:07:57 naddy Exp $

COMMENT=		archive files using LZW compression (.lzh files)
VERSION=		1.14i
DASH_VER=		2
DISTNAME=		lha-${VERSION:S/.//}
PKGNAME=		lha-${VERSION}-${DASH_VER}
CATEGORIES=		archivers
HOMEPAGE=		http://www2m.biglobe.ne.jp/~dolphin/lha/lha.htm

# Restrictive
PERMIT_PACKAGE_CDROM=	"requires advance notification"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"requires advance notification"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www2m.biglobe.ne.jp/~dolphin/lha/prog/ \
		ftp://ftp.win.ne.jp/pub/misc/

EXTRA_MAKE_FLAGS=	OPTIMIZE=${CFLAGS:Q} \
			MACHINE="-DUSESTRCASECMP -DGETTIMEOFDAY -DMKTIME \
			    -DTZSET -DSYSV_SYSTEM_DIR" \
			SWITCHES="-DNEED_INCREMENTAL_INDICATOR -DEUC \
			    -DSUPPORT_LH7 -DMKSTEMP"

EXTRA_FAKE_FLAGS=	BINDIR=${WRKINST:Q}${PREFIX:Q}/bin \
			MANDIR=${WRKINST:Q}${PREFIX:Q}/man/ja_JP.EUC \
			MANSECT=1 INSTALL= \
			INSTALLBIN=${INSTALL_PROGRAM:Q} \
			INSTALLMAN=${INSTALL_MAN:Q}

NO_REGRESS=		Yes

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/man/ja_JP.EUC/man1

.include <bsd.port.mk>
