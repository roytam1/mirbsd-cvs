# $MirOS: ports/infrastructure/pkgtools/pkg/Makefile,v 1.1.7.1 2005/03/18 15:47:16 tg Exp $
# $OpenBSD: Makefile,v 1.2 2001/04/02 17:25:53 espie Exp $

PROG=	pkg
SRCS=
INSTALL_STRIP=

${PROG}: ${PROG}.pl
	sed -e 's#@@dbdir@@#${DB_DIR}#' <$> >$@

.include <bsd.prog.mk>
