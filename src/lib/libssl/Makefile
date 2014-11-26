# $MirOS: src/lib/libssl/Makefile,v 1.6 2007/07/05 22:18:13 tg Exp $
# $OpenBSD: Makefile,v 1.13 2002/09/03 18:59:55 markus Exp $

SUBDIR=	crypto ssl man

afterinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m ${NONBINMODE} \
	    ${.CURDIR}/openssl.pc ${DESTDIR}/usr/libdata/pkgconfig/

distribution:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	   ${.CURDIR}/openssl.cnf ${DESTDIR}/etc/ssl/openssl.cnf
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${CONFGRP} -m ${NONBINMODE} \
	   ${.CURDIR}/x509v3.cnf ${DESTDIR}/etc/ssl/x509v3.cnf

prereq: _SUBDIRUSE

.include <bsd.subdir.mk>
