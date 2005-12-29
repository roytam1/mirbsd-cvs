# $MirOS: ports/multimedia/win32-codecs/Makefile,v 1.7 2005/12/28 17:44:47 tg Exp $
# $OpenBSD: Makefile,v 1.9 2003/11/13 09:10:19 kevlo Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=	"Huge compilation of mostly Win32 binary codecs for MPlayer"
RESPONSIBLE=	Thorsten Glaser <tg@66h.42h.de>
_V=		20050412
DISTNAME=	all-${_V}
PKGNAME=	win32-codecs-${_V}-2
CATEGORIES=	graphics multimedia

# probably bad, includes DivX ;-) v3 codecs.
PERMIT_PACKAGE_CDROM=   "Unsure of codecs' licences"
PERMIT_PACKAGE_FTP=     "Unsure of codecs' licences"
PERMIT_DISTFILES_CDROM= "Unsure of codecs' licences"
PERMIT_DISTFILES_FTP=   "Unsure of codecs' licences"

MASTER_SITES=	\
		http://www1.mplayerhq.hu/MPlayer/releases/codecs/ \
		http://www2.mplayerhq.hu/MPlayer/releases/codecs/ \
		ftp://mplayerhq.hu/MPlayer/releases/codecs/ \
		ftp://ftp.lug.udel.edu/MPlayer/releases/codecs/ \
		ftp://ftp2.mplayerhq.hu/MPlayer/releases/codecs/ \
		ftp://ftp3.mplayerhq.hu/MPlayer/releases/codecs/ \
		ftp://ftp5.mplayerhq.hu/MPlayer/releases/codecs/
MASTER_SITES0=	${_MASTER_SITE_MIRBSD}
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} \
		morecodecs-20051229.cgz:0
EXTRACT_SUFX=	.tar.bz2

NO_BUILD=	Yes
NO_REGRESS=	Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/codecs
	${INSTALL_DATA} ${WRKDIR}/${DISTNAME}/* ${PREFIX}/lib/codecs/
	rm -f ${PREFIX}/lib/codecs/l3codec*
	${INSTALL_DATA} ${WRKDIR}/morecodecs/* ${PREFIX}/lib/codecs/

.include <bsd.port.mk>
