# $MirOS$

PROG=	pkg_upgrade
SRCS=	pkg_upgrade.sh
INSTALL_STRIP=

NOMAN=	Yes

${PROG}: ${SRCS}
	sed -e 's#@@dbdir@@#${DB_DIR}#' <$< >$@

depend:

.include <bsd.prog.mk>
