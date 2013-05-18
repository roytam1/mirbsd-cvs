# $MirOS: src/gnu/usr.sbin/sendmail/Makefile,v 1.3 2008/05/07 13:15:14 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/06/29 04:07:49 millert Exp $

# We only use these libs internally
.if !make(install)
SUBDIR= libsmutil libsmdb libsm
.else
SUBDIR=
.endif

# The bits we install
SUBDIR+= libmilter sendmail mailstats makemap praliases smrsh editmap cf/cf

# Extra bits we don't build/install right now
#SUBDIR+= mail.local rmail vacation

# These just get installed verbatim
.if make(install)
SUBDIR+= doc/op cf
.endif

afterinstall:
	${INSTALL} -c -o ${DOCOWN} -g ${DOCGRP} -m ${DOCMODE} LICENSE \
	    ${DESTDIR}${DOCDIR}/legal/LICENCE.smtpd

.include <bsd.subdir.mk>
