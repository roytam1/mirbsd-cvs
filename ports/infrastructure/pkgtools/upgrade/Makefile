# $MirOS: ports/infrastructure/pkgtools/upgrade/Makefile,v 1.3 2006/08/08 18:53:02 bsiegert Exp $

PROG=	pkg_upgrade
SRCS=	pkg_upgrade.sh
INSTALL_STRIP=

${PROG}: ${SRCS}
	sed \
	    -e 's#@@dbdir@@#${PKG_DB_DIR}#' \
	    -e 's#!/bin/mksh#!'${MKSH:Q}'' \
	    <$< >$@

depend:

.include <bsd.prog.mk>
