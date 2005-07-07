# $MirOS$
# $OpenBSD: Makefile,v 1.24 2002/12/29 20:08:46 fgsch Exp $

COMMENT=	"IJG's JPEG compression utilities"
DISTNAME=	jpegsrc.v6b
PKGNAME=	jpeg-6b-2
CATEGORIES=	graphics
MASTER_SITES=	ftp://ftp.uu.net/graphics/jpeg/ \
		ftp://ftp.shellhung.org/pub/Mirror/enlightenment/enlightenment/libs/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}/jpeg-6b

post-patch:
	cp ${FILESDIR}/jconfig.h ${WRKSRC}
	cp ${FILESDIR}/Makefile ${WRKSRC}
.for dir in lib cjpeg djpeg jpegtran rdjpgcom wrjpgcom
	mkdir ${WRKSRC}/${dir}
	cp ${FILESDIR}/Makefile.${dir} ${WRKSRC}/${dir}/Makefile
.endfor

.include <bsd.port.mk>
