# $MirOS: ports/infrastructure/pkgtools/upgrade/Makefile,v 1.1.2.2 2005/09/11 01:05:45 tg Exp $

PROG=	pkg_upgrade
SRCS=	pkg_upgrade.sh
INSTALL_STRIP=

NOMAN=	Yes

${PROG}: ${SRCS}
	sed -e 's#@@dbdir@@#${PKG_DB_DIR}#' <$< >$@

depend:

.include <bsd.prog.mk>
