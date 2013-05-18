# $MirOS: ports/games/adom/Makefile,v 1.3 2005/04/11 15:55:24 tg Exp $
# $OpenBSD: Makefile,v 1.18 2003/10/18 15:46:53 sturm Exp $
# Author: Thomas Biskup <rpg@saranxis.ruhr.de>

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=			Ancient Domains of Mystery - roguelike
DISTNAME=	adom-1.1.1p1
CATEGORIES=	games
MASTER_SITES=   http://www.adom.de/adom/download/linux/
HOMEPAGE=	http://www.adom.de/
DISTFILES=	adom-111-elf.tar.gz

NO_BUILD=	Yes
NO_REGRESS=	Yes


PERMIT_PACKAGE_CDROM=	"no modify"
PERMIT_PACKAGE_FTP=	"no modify"
PERMIT_DISTFILES_CDROM=	"no modify"
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}/adom

ADOM_DOC=	${PREFIX}/share/doc/adom

# cage adom into its specific group if you don't trust the binary
ADOMOWN?=	games

# can't be changed except by patching the binary
HISCORE_DIR=	/var/lib/adom

RUN_DEPENDS+=	:redhat_base-*:emulators/redhat/base

do-install:
	@${INSTALL_DATA_DIR} ${ADOM_DOC}
	@cd ${WRKSRC} && ${INSTALL_DATA} adomfaq.txt manual.doc readme.1st ${ADOM_DOC}
# Kludge to work around the absence of libncurses.
	@cd ${WRKSRC} && sed -e s,libncurses.so.5,libncurses.so.4, adom >adom.new
	@cd ${WRKSRC} && ${INSTALL} ${INSTALL_COPY} \
		-o ${BINOWN} -g ${ADOMOWN} -m 2555 adom.new ${PREFIX}/bin/adom
	@${INSTALL} -d -o ${SHAREOWN} -g ${ADOMOWN} -m 775 ${WRKINST}${HISCORE_DIR}

.include <bsd.port.mk>
