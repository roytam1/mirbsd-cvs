# $MirOS: ports/infrastructure/pkgtools/upgrade/Makefile,v 1.4 2009/03/29 13:04:06 tg Exp $

PROG=	pkg_upgrade
SRCS=	pkg_upgrade.sh
INSTALL_STRIP=

${PROG}: ${SRCS}
	sed \
	    -e 's,@@dbdir@@,${PKG_DB_DIR},' \
	    -e 's,#!/bin/mksh,#!'${MKSH:Q}',' \
	    <$< >$@

depend:

.include <bsd.prog.mk>
