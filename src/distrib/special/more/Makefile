# $MirOS: src/distrib/special/more/Makefile,v 1.2 2006/05/26 18:52:34 tg Exp $
# $OpenBSD: Makefile,v 1.8 2003/05/29 17:33:53 deraadt Exp $

PROG=		more
CPPFLAGS+=	-I.
DPADD=		${LIBOCURSES}
LDADD=		-locurses
CLEANFILES+=	morehelp.h

beforedepend: morehelp.h

morehelp.h: ${.CURDIR}/more.help
	echo -n 'const char *more_help = "' >$@
	sed -e 's/[\\"]/\\&/g' -e 's/$$/\\n\\/' ${.CURDIR}/more.help >>$@
	echo '";' >>$@

.include <bsd.prog.mk>
