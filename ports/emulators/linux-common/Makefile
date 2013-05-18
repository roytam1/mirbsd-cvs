# $MirOS: ports/emulators/linux-common/Makefile,v 1.4 2006/09/14 00:09:10 tg Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

CATEGORIES=		emulators
COMMENT=		common files for compat_linux(8)
EMUL=			linux
PKGNAME=		linux-common-20070101-0

# MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

NO_DISTFILES=		Yes
NO_CHECKSUM=		Yes
NO_REGRESS=		Yes

do-build:
	sed -e 's!@LOCALBASE@!${LOCALBASE}!g' \
	    -e 's!@MKSH@!${MKSH}!g' \
	    <${FILESDIR}/linuxctl >${WRKSRC}/linuxctl
	echo -n >${WRKSRC}/mtab.empty

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/emul/linux
	${INSTALL_SCRIPT} ${WRKSRC}/linuxctl ${PREFIX}/emul/linux/
	${INSTALL_DATA} ${WRKSRC}/mtab.empty ${PREFIX}/emul/linux/

.include <bsd.port.mk>
