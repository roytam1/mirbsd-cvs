# $MirOS: ports/sysutils/cdrtools/Makefile,v 1.2 2005/07/07 21:26:31 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2004/02/13 17:25:51 sturm Exp $

COMMENT=			ISO 9660 filesystem and CD creation tools
DISTNAME=		cdrtools-2.00.3
PKGNAME=		${DISTNAME}-1
CATEGORIES=		sysutils
HOMEPAGE=		http://www.fokus.gmd.de/research/cc/glone/employees/joerg.schilling/private/cdrecord.html
MASTER_SITES=		ftp://ftp.berlios.de/pub/cdrecord/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_SCHILY=		Yes
CONFIGURE_STYLE=	No

FAKE_FLAGS=		INS_BASE=${WRKINST}${PREFIX} \
			INSUSR=${BINOWN} \
			INSGRP=${BINGRP} \
			INSMODEX=${BINMODE} \
			INSMODEF=${SHAREMODE} \
			MANSECT=man1 \
			MANSUFFIX=1

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/cdrtools
	${INSTALL_DATA} ${WRKSRC}/README.OpenBSD \
	    ${PREFIX}/share/doc/cdrtools/README.MirPorts
	@strip ${PREFIX}/bin/* 
	@cd ${PREFIX}/man/man1; \
		for i in devdump.1 isovfy.1 ; do \
			ln -s isoinfo.1 $$i ; \
		done

.include <bsd.port.mk>
