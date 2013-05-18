# $MirOS: src/lib/libssl/Makefile,v 1.4 2007/05/08 21:54:24 tg Exp $
# $OpenBSD: Makefile,v 1.13 2002/09/03 18:59:55 markus Exp $

SUBDIR=	crypto ssl man

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/openssl.pc ${DESTDIR}/usr/share/pkgconfig/

distribution:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	   ${.CURDIR}/openssl.cnf ${DESTDIR}/etc/ssl/openssl.cnf
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	   ${.CURDIR}/x509v3.cnf ${DESTDIR}/etc/ssl/x509v3.cnf

.include <bsd.subdir.mk>
