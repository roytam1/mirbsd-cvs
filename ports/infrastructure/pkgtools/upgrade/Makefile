# $MirOS: ports/infrastructure/pkgtools/upgrade/Makefile,v 1.1 2005/08/21 13:02:59 bsiegert Exp $

PROG=	pkg_upgrade
SRCS=	pkg_upgrade.sh
INSTALL_STRIP=

NOMAN=	Yes

${PROG}: ${SRCS}
	sed -e 's#@@dbdir@@#${DB_DIR}#' <$< >$@

depend:

.include <bsd.prog.mk>
