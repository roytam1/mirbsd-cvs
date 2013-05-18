# $MirOS: ports/net/BitTorrent/Makefile,v 1.4 2005/11/25 07:54:00 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/04/15 03:41:14 jolan Exp $

COMMENT=			cooperative file distribution system implemented in Python
DISTNAME=	BitTorrent-3.4.2
CATEGORIES=	net
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=bittorrent/}
HOMEPAGE=	http://bittorrent.com/

# MIT
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
# When upgrading to 4.2, uncomment these:
## proprietary licence
#PERMIT_PACKAGE_CDROM=	No
#PERMIT_PACKAGE_FTP=	No

MODULES=	lang/python

post-configure:
	for f in ${WRKBUILD}/bt*.py; do \
		print '%g#/usr/bin/env python#s##/usr/bin/env' \
		    'python${MODPY_VERSION}#g\nwq' | ed -s $$f; \
	done

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/BitTorrent
	${INSTALL_DATA} ${WRKSRC}/README.txt ${PREFIX}/share/doc/BitTorrent/
	${INSTALL_DATA} ${FILESDIR}/README.OpenBSD \
	    ${PREFIX}/share/doc/BitTorrent/README.MirPorts

do-regress:
	cd ${WRKBUILD} && ${MODPY_BIN} ./bttest.py

.include <bsd.port.mk>
