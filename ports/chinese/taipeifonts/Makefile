# $MirOS: ports/chinese/taipeifonts/Makefile,v 1.3 2007/04/11 17:05:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.21 2004/02/03 07:28:12 sturm Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	extra chinese fonts

DISTNAME=       zh-fonts-taipei-1.01
CATEGORIES=     chinese x11

DIST_SUBDIR=    zh-fonts

MASTER_SITES=	ftp://ftp.nsysu.edu.tw/Linux/packages/chinese/fonts/taipeifont/ \
		ftp://ftp.ee.ncku.edu.tw/pub/Linux/packages/chinese/fonts/taipeifont/ \
		ftp://ftp.shellhung.org/pub/OpenBSD/packages/chinese/taipeifont/


PERMIT_DISTFILES_CDROM= "no licence"
PERMIT_DISTFILES_FTP=   "no licence"
PERMIT_PACKAGE_CDROM=   "no licence"
PERMIT_PACKAGE_FTP=     "no licence"

FONTS=		taipei16.pcf.gz taipeik20.pcf.gz taipeim20.pcf.gz \
		taipei24.pcf.gz taipeik24.pcf.gz taipeim24.pcf.gz

DISTFILES=	${FONTS}
NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*
EXTRACT_ONLY=

CONFIGURE_STYLE=	imake
USE_X11=	Yes

FONTDIR=	${PREFIX}/lib/X11/fonts/chinese

post-extract:
	@mkdir -p ${WRKDIST}
	@cp ${FILESDIR}/Imakefile ${FILESDIR}/taipei.alias ${WRKDIST}
	@for i in ${FONTS} ; do cp $(FULLDISTDIR)/$$i ${WRKDIST}; done

post-install:
	@cd ${FONTDIR} && mv fonts.alias fonts.alias-taipei

.include <bsd.port.mk>
