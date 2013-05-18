# $MirOS: src/share/doc/Makefile,v 1.2 2005/03/06 19:38:14 tg Exp $
# $OpenBSD: Makefile,v 1.3 2004/02/12 10:03:31 jmc Exp $
# @(#)Makefile	8.1 (Berkeley) 6/5/93

.MAIN: all

.if !make(install)
  SUBDIR= legal
.endif

.if make(install)
  SUBDIR!= print */Makefile | sed 's,/Makefile[[:>:]],,g'
.endif

afterinstall:
	${INSTALL} -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} \
	    README ${DESTDIR}${DOCDIR}/

.include <bsd.subdir.mk>
