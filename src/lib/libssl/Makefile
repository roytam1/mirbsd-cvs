# $MirOS: src/lib/libssl/Makefile,v 1.2 2005/04/26 15:36:17 tg Exp $
# $OpenBSD: Makefile,v 1.13 2002/09/03 18:59:55 markus Exp $

SUBDIR=	crypto ssl man

distribution:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	   ${.CURDIR}/openssl.cnf ${DESTDIR}/etc/ssl/openssl.cnf && \
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	   ${.CURDIR}/x509v3.cnf ${DESTDIR}/etc/ssl/x509v3.cnf

.include <bsd.subdir.mk>
