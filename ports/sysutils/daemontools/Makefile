# $MirOS: ports/sysutils/daemontools/Makefile,v 1.14 2008/11/08 23:04:06 tg Exp $

COMMENT=		collection of tools for managing unix services
CATEGORIES=		sysutils
DISTNAME=		daemontools-0.76
DASH_VER=		4
MANVER=			20020131
HOMEPAGE=		http://cr.yp.to/daemontools.html
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# Public Domain: http://cr.yp.to/distributors.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

DISTFILES=		${DISTNAME}${EXTRACT_SUFX} \
			${DISTNAME}-man-${MANVER}${EXTRACT_SUFX}:0
MASTER_SITES=		http://cr.yp.to/daemontools/
MASTER_SITES0=		http://smarden.org/pape/djb/manpages/
WRKDIST=		${WRKDIR}
NO_REGRESS=		Yes

MAN8LIST=		envdir envuidgid fghack multilog setlock setuidgid \
			softlimit supervise svc svok svscan svstat tai64n \
			tai64nlocal svscanboot pgrphack readproctitle

BINLIST=		envdir envuidgid fghack multilog pgrphack \
			readproctitle setlock setuidgid softlimit \
			supervise svc svok svscan svstat tai64n tai64nlocal

do-build:
	if [[ ! -e ${WRKSRC}/admin/${DISTNAME}/src/home ]]; then \
		print -r -- ${_PASS_CC:T:Q} ${CFLAGS:M*:Q} \
		    >${WRKSRC}/admin/${DISTNAME}/src/conf-cc; \
		print -r -- ${_PASS_CC:T:Q} ${CFLAGS:M*:Q} ${LDFLAGS:M*:Q} \
		    >${WRKSRC}/admin/${DISTNAME}/src/conf-ld; \
		print -r -- ${PREFIX:Q} >${WRKSRC}/admin/${DISTNAME}/src/home; \
	fi
	cd ${WRKSRC}/admin/${DISTNAME}/src && \
	    ${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} it

do-install:
.for i in ${BINLIST}
	${INSTALL_PROGRAM} ${WRKSRC}/admin/${DISTNAME}/src/$i ${PREFIX}/bin/
.endfor
	for a in ${WRKSRC}/admin/${DISTNAME}/src/svscanboot \
	    ${WRKDIR}/daemontools-man/svscanboot.8; do \
		chmod u+w $$a; \
		print ',g!/usr/local!s!!${TRUEPREFIX}!g\nwq' | ed -s $$a; \
	done
	print ',g!^/command!s!!${TRUEPREFIX}/bin!\nwq' | \
	    ed -s ${WRKSRC}/admin/${DISTNAME}/src/svscanboot
	${INSTALL_SCRIPT} ${WRKSRC}/admin/${DISTNAME}/src/svscanboot \
	    ${PREFIX}/bin/
.for i in ${MAN8LIST}
	${INSTALL_MAN} ${WRKDIR}/daemontools-man/$i.8 ${PREFIX}/man/man8/
.endfor

.include <bsd.port.mk>
