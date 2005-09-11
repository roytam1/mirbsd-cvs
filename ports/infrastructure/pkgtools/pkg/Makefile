# $MirOS: ports/infrastructure/pkgtools/pkg/Makefile,v 1.2 2005/05/21 00:16:06 tg Exp $
# $OpenBSD: Makefile,v 1.2 2001/04/02 17:25:53 espie Exp $

PROG=	pkg
SRCS=
INSTALL_STRIP=

${PROG}: ${PROG}.pl
	sed -e 's#@@dbdir@@#${PKG_DB_DIR}#' <$> >$@

.include <bsd.prog.mk>
