# $MirOS: ports/japanese/JMdict/Makefile,v 1.1 2006/10/06 20:09:25 tg Exp $
# $NetBSD: Makefile,v 1.5 2006/07/04 06:23:00 wiz Exp $

COMMENT=		Japanese-Multilingual electronic dictionary
CATEGORIES=		japanese misc
DISTNAME=		JMdict
VSN=			2006.10
PKGNAME=		${DISTNAME}-${VSN}-${DASH_VER}
HOMEPAGE=		http://www.csse.monash.edu.au/~jwb/j_jmdict.html \
			http://www.csse.monash.edu.au/~jwb/edict.html

# Creative Commons by-sa 2.5
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://japanology.arts.kuleuven.ac.be/mirrors/monash/ \
			http://www.bcit-broadcast.com/monash/ \
			ftp://ftp.cc.monash.edu.au/pub/nihongo/ \
			ftp://ftp.nrc.ca/pub/packages/nihongo/ \
			ftp://ftp.sedl.org/pub/mirrors/nihongo/ \
			ftp://ftp.net.usf.edu/pub/monash/ \
			ftp://ftp.u-aizu.ac.jp/pub/SciEng/nihongo/ftp.cc.monash.edu.au/ \
			ftp://ftp.funet.fi/pub/culture/japan/mirrors/monash/pub/nihongo/
MASTER_SITES0=		http://www.csse.monash.edu.au/~jwb/edrdg/
EXTRACT_SUFX=		.gz
DISTFILES=		JMdict.dtd JMdict.gz JMdict.inf jmdict_proj_desc.html \
			licence.html:0
WRKDIST=		${WRKDIR}
DIST_SUBDIR=		${DISTNAME}-${VSN}
EXTRACT_ONLY=		JMdict.gz
NO_BUILD=		Yes
NO_REGRESS=		Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/JMdict ${PREFIX}/share/doc/JMdict
	${INSTALL_DATA} ${WRKSRC}/JMdict ${DISTDIR}/${DIST_SUBDIR}/JMdict.dtd \
	    ${PREFIX}/share/JMdict/
	cd ${DISTDIR}/${DIST_SUBDIR} && ${INSTALL_DATA} JMdict.inf \
	    jmdict_proj_desc.html licence.html ${PREFIX}/share/doc/JMdict/

.include <bsd.port.mk>
