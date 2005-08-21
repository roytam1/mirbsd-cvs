# $MirOS: ports/multimedia/win32-codecs/Makefile,v 1.5 2005/07/07 21:23:58 bsiegert Exp $
# $OpenBSD: Makefile,v 1.9 2003/11/13 09:10:19 kevlo Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=	"Huge compilation of mostly Win32 binary codecs for MPlayer"
RESPONSIBLE=	Thorsten Glaser <tg@66h.42h.de>
_V=		20050412
DISTNAME=	all-${_V}
PKGNAME=	win32-codecs-${_V}-0
CATEGORIES=	graphics multimedia

# royalty-free decoder; for personal use royalty-free encoder up to 56 kb/s
FASTENC=	FastENC

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
DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${FASTENC}${EXTRACT_SUFX}:0
EXTRACT_SUFX=	.tar.bz2

NO_BUILD=	Yes
NO_REGRESS=	Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/codecs
	${INSTALL_DATA} ${WRKDIR}/${DISTNAME}/* ${PREFIX}/lib/codecs/
	rm -f ${PREFIX}/lib/codecs/l3codeca.acm
	${INSTALL_DATA} ${WRKDIR}/${FASTENC}/* ${PREFIX}/lib/codecs/

.include <bsd.port.mk>
