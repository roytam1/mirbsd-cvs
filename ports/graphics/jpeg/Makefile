# $MirOS: ports/graphics/jpeg/Makefile,v 1.8 2014/11/26 19:29:31 tg Exp $
# $OpenBSD: Makefile,v 1.24 2002/12/29 20:08:46 fgsch Exp $

COMMENT=		IJG's JPEG compression utilities
DISTNAME=		jpegsrc.v6b
PKGNAME=		jpeg-6b-7
CATEGORIES=		graphics
DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			jpeg-ari-28mar98.tar.gz:0
MASTER_SITES=		ftp://ftp.uu.net/graphics/jpeg/ \
			ftp://ftp.shellhung.org/pub/Mirror/enlightenment/enlightenment/libs/
MASTER_SITES0=		http://sylvana.net/jpeg-ari/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/jpeg-6b

.include <mirports.sys.mk>

pre-patch:
	# Prepare for arithmetic compression
	cp ${WRKDIR}/jpeg-ari-28mar98/patchv6b/*.[ch] ${WRKSRC}/
	# Integrate arithmetic compression
	cp ${WRKDIR}/jpeg-ari-28mar98/*.c ${WRKSRC}/

post-patch:
	cp ${FILESDIR}/jconfig.h ${WRKSRC}
	cp ${FILESDIR}/Makefile ${WRKSRC}
.for dir in lib cjpeg djpeg jpegtran rdjpgcom wrjpgcom
	mkdir ${WRKSRC}/${dir}
	cp ${FILESDIR}/Makefile.${dir} ${WRKSRC}/${dir}/Makefile
.endfor

.include <bsd.port.mk>
