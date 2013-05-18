# $MirOS: ports/misc/cdrdao/Makefile,v 1.1.7.1 2005/03/18 15:50:25 tg Exp $
# $OpenBSD: Makefile,v 1.18 2002/11/08 15:35:19 fgsch Exp $

COMMENT=			write audio/data CD-Rs in disk-at-once mode
DISTNAME=	 	cdrdao-1.1.7
CATEGORIES=		audio misc
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=cdrdao/}
DISTFILES=		${DISTNAME}.src${EXTRACT_SUFX}
HOMEPAGE=		http://cdrdao.sourceforge.net/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_SCHILY=		Yes
USE_CXX=		Yes
CONFIGURE_STYLE=	gnu dest
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/paranoia ${WRKSRC}/scsilib
CONFIGURE_ARGS+=	--with-posix-threads=no --without-lame \
			--with-gtkmm-prefix=/nonexistent --disable-gtkmmtest

post-install:
	@strip ${PREFIX}/bin/cdrdao ${PREFIX}/bin/toc2cue
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/cdrdao
	cd ${WRKDIST} && ${INSTALL_DATA} README README.PlexDAE \
	    ${PREFIX}/share/doc/cdrdao

.include <bsd.port.mk>
