# $MirOS: src/usr.sbin/upkg/Makefile,v 1.1 2005/08/23 20:57:28 bsiegert Exp $

PROG=	upkg
SRCS=	upkg.sh
INSTALL_STRIP=

NOMAN=	Yes

${PROG}: ${SRCS}
	sed -e 's#@@dbdir@@#${DB_DIR}#' <$< >$@

.include <bsd.prog.mk>
