# $MirOS: ports/archivers/rar-linux/Makefile,v 1.7 2006/01/01 03:15:06 tg Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

CATEGORIES=		archivers
COMMENT=		"commercial RAR archiver binary"
V=			3.4.1
DISTNAME=		rarlinux-${V}
FULLPKGNAME=		rar-${V}-2-linux
MASTER_SITES=		http://www.rarlab.com/rar/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
HOMEPAGE=		http://www.win-rar.com/index.php

# try-before-buy, 40 day test version
PERMIT_DISTFILES_CDROM=	"imposes restrictions"
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	"Shareware"
PERMIT_PACKAGE_FTP=	"Shareware"

NO_BUILD=		Yes
NO_REGRESS=		Yes

WRKDIST=		${WRKDIR}/rar

do-configure:

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/rar
	${INSTALL_PROGRAM} ${WRKSRC}/rar_static ${PREFIX}/bin/rar
	${INSTALL_SCRIPT} ${WRKSRC}/default.sfx ${PREFIX}/lib/
.for _i in file_id.diz license.txt order.htm rar.txt rarfiles.lst \
    readme.txt technote.txt whatsnew.txt
	${INSTALL_DATA} ${WRKSRC}/${_i} ${PREFIX}/share/doc/rar/
.endfor

.include <bsd.port.mk>
