# $MirOS$

PROG=	pkg_scan
SRCS=	pkg_scan.sh
INSTALL_STRIP=

${PROG}: ${SRCS}
	sed -e 's#@@dbdir@@#${DB_DIR}#' <$< >$@

depend:

.include <bsd.prog.mk>
