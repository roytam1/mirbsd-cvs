# $MirOS: ports/net/djbdns/files/build/man/Makefile,v 1.1.201.1 2005/05/14 23:21:07 tg Exp $

MAN=		qualification.5
NOPROG=		Yes

.include "../Makefile.inc"

qualification.5: ${mandir}/qualification.5
	sed 's#/etc/dnsrewrite#@@SYSCONFDIR@@/dnsrewrite#g' <$> >$@

.include <bsd.prog.mk>
