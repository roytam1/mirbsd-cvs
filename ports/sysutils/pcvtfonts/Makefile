# $MirOS: ports/sysutils/pcvtfonts/Makefile,v 1.4 2008/12/07 18:58:05 tg Exp $

COMMENT=		OpenBSD wscons/pcvt text console fonts
CATEGORIES=		sysutils
MCZ_FETCH=		Yes
CVS_DISTFILE=		pcvtfonts
VSN=			3.9
PKGNAME=		${CVS_DISTFILE}-${VSN}-${DASH_VER}
CVS_DISTREPO=		:ext:anoncvs@anoncvs.ca.openbsd.org:/cvs
CVS_DISTTAGS=		OPENBSD_${VSN:S/./_/}_BASE
CVS_DISTMODS=		src/share/misc/pcvtfonts src/share/Makefile.inc
WRKSRC=			${WRKDIR}/src/share/misc/pcvtfonts
HOMEPAGE=		http://www.openbsd.org/faq/faq7.html\#80x50

# 4-clause UCB
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

EXTRA_XAKE_FLAGS+=	FONTDIR=${TRUEPREFIX}/share/${CVS_DISTFILE}
EXTRA_XAKE_FLAGS+=	LIBOWN=${BINOWN} LIBGRP=${BINGRP}

.include <bsd.port.mk>
