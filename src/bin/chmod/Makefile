# $MirOS: src/bin/chmod/Makefile,v 1.3 2005/11/21 22:34:15 tg Exp $
# $OpenBSD: Makefile,v 1.7 2001/09/06 18:52:55 mickey Exp $
#-
# this is chmod(1), but installs as chgrp first due to DEBUGPROGS weirdness

PROG=	chgrp
SRCS=	chmod.c
MAN=	chmod.1 chgrp.1 chown.8 chflags.1
LINKS=	${BINDIR}/chgrp ${BINDIR}/chmod \
	${BINDIR}/chmod /sbin/chown

afterinstall:
	-rm -f ${DESTDIR}/usr/bin/chflags
	cd ${DESTDIR}/usr/bin && ln -s ../..${BINDIR}/chmod chflags

.include <bsd.prog.mk>
