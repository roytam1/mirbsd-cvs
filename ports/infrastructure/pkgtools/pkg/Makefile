# $MirOS$
# $OpenBSD: Makefile,v 1.2 2001/04/02 17:25:53 espie Exp $

PROG=	pkg
SRCS=

${PROG}: ${PROG}.pl
	sed -e 's#@@dbdir@@#${DB_DIR}#' <$> >$@

.include <bsd.prog.mk>
