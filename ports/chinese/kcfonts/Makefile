# $MirOS: ports/chinese/kcfonts/Makefile,v 1.3 2007/04/11 17:05:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2004/02/03 07:28:12 sturm Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	extra chinese fonts

DISTNAME=       zh-fonts-kc-1.05
CATEGORIES=     chinese x11


PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes
PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes

MASTER_SITES=	ftp://ftp.nsysu.edu.tw/Linux/packages/chinese/fonts/KCFONTS/ \
		ftp://ftp.shellhung.org/pub/OpenBSD/packages/chinese/KCFONTS/
DIST_SUBDIR=    zh-kcfonts
DISTFILES=	${FONTS}

CONFIGURE_STYLE= imake
USE_X11=	Yes

EXTRACT_ONLY=
NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*

FONTS=		kc8x15.pcf.gz kc12x24.pcf.gz kc15f.pcf.gz kc24f.pcf.gz

FONTDIR=	${PREFIX}/lib/X11/fonts/chinese

post-extract:
	@mkdir -p ${WRKDIST}
	@cp ${FILESDIR}/Imakefile ${FILESDIR}/kc.alias ${WRKDIST}
	@for i in ${FONTS} ; do cp $(FULLDISTDIR)/$$i ${WRKDIST}; done

post-install:
	@cd ${FONTDIR} && mv fonts.alias fonts.alias-kc

.include <bsd.port.mk>
