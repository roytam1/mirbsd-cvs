# $MirOS: ports/infrastructure/pkgtools/upgrade/Makefile,v 1.1.2.3 2005/09/11 01:14:13 tg Exp $

PROG=	pkg_upgrade
SRCS=	pkg_upgrade.sh
INSTALL_STRIP=

NOMAN=	Yes

${PROG}: ${SRCS}
	sed -e 's#@@dbdir@@#${PKG_DB_DIR}#' <$< >$@

depend:

.include <bsd.prog.mk>
