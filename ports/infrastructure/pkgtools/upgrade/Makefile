# $MirOS: ports/infrastructure/pkgtools/upgrade/Makefile,v 1.2 2005/09/12 22:53:28 tg Exp $

PROG=	pkg_upgrade
SRCS=	pkg_upgrade.sh
INSTALL_STRIP=

${PROG}: ${SRCS}
	sed -e 's#@@dbdir@@#${PKG_DB_DIR}#' <$< >$@

depend:

.include <bsd.prog.mk>
