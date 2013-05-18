# $MirOS: ports/sysutils/cdrtools/Makefile,v 1.3 2006/09/14 00:13:29 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/02/13 17:25:51 sturm Exp $

#XXX TODO: integrate diffs from base mkisofs

COMMENT=		ISO 9660 filesystem and CD creation tools
DISTNAME=		cdrtools-2.00.3
DASH_VER=		2
CATEGORIES=		sysutils
HOMEPAGE=		http://www.fokus.gmd.de/research/cc/glone/employees/joerg.schilling/private/cdrecord.html
MASTER_SITES=		ftp://ftp.berlios.de/pub/cdrecord/

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>

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
.if !empty(INSTALL_STRIP)
	@strip ${PREFIX}/bin/*
.endif
	@cd ${PREFIX}/man/man1; \
		for i in devdump.1 isovfy.1 ; do \
			ln -s isoinfo.1 $$i ; \
		done

.include <bsd.port.mk>
