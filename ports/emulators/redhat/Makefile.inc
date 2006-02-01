# $MirOS: ports/emulators/redhat/Makefile.inc,v 1.3 2005/04/11 15:55:15 tg Exp $
# $OpenBSD: Makefile.inc,v 1.7 2002/12/29 15:06:49 fgsch Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

CATEGORIES=		emulators
EMUL=			linux

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITE_REDHAT=\
		ftp://ftp.uni-bayreuth.de/pub/redhat.com/ \
		ftp://ftp.funet.fi/pub/mirrors/ftp.redhat.com/pub/ \
		ftp://ftp.redhat.com/pub/

DIST_SUBDIR=	rpm
EXTRACT_ONLY=

BUILD_DEPENDS+=	::converters/rpm2cpio

NO_BUILD=	Yes
NO_REGRESS=	Yes
EMDIR=		${PREFIX}/emul/redhat
PL=		7

pre-install:
	@${INSTALL_DATA_DIR} ${EMDIR}
