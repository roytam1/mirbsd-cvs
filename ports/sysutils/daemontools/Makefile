# $MirOS$

COMMENT=	"collection of tools for managing unix services"
CATEGORIES=	sysutils
DISTNAME=	daemontools-0.76
HOMEPAGE=	http://cr.yp.to/daemontools.html
RESPONSIBLE=	Thorsten Glaser <x86@ePost.de>

# May distribute patches.
# Must not distribute binaries.
# Must not distribute distfiles.
PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	No
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	"http://cr.yp.to/distributors.html"

DISTFILES=	${DISTNAME}${EXTRACT_SUFX} ${DISTNAME}-man${EXTRACT_SUFX}:0
MASTER_SITES=	http://cr.yp.to/daemontools/
MASTER_SITES0=	${_MASTER_SITE_MIRBSD}

MAN8LIST=	envdir envuidgid fghack multilog setlock setuidgid softlimit \
		supervise svc svok svscan svstat tai64n tai64nlocal \
		svscanboot pgrphack readproctitle

BINLIST=	envdir envuidgid fghack multilog pgrphack readproctitle \
		setlock setuidgid softlimit supervise svc svok svscan \
		svstat tai64n tai64nlocal

WRKDIST=	${WRKDIR}
PATCH_LIST=
.if ${OSname} == "mirbsd" && ${OSrev} >= 8
PATCH_LIST+=	patch-admin_daemontools-0_76_src_tai_now_c \
		patch-admin_daemontools-0_76_src_taia_now_c
.endif

do-build:
	@echo ${CC} ${CFLAGS} >${WRKSRC}/admin/${DISTNAME}/src/conf-cc
	@echo ${CC} ${CFLAGS} ${LDFLAGS} >${WRKSRC}/admin/${DISTNAME}/src/conf-ld
	@echo ${PREFIX} > ${WRKSRC}/admin/${DISTNAME}/src/home
	cd ${WRKSRC}/admin/${DISTNAME}/src && make it

do-install:
.for i in ${BINLIST}
	${INSTALL_PROGRAM} ${WRKSRC}/admin/${DISTNAME}/src/$i ${PREFIX}/bin
.endfor
	cd ${WRKSRC}/admin/${DISTNAME}/src && \
		sed s,/command/svc,/usr/local/bin/svc, <svscanboot >svscanboot.new
	${INSTALL_SCRIPT} ${WRKSRC}/admin/${DISTNAME}/src/svscanboot.new ${PREFIX}/bin/svscanboot
.for i in ${MAN8LIST}
	${INSTALL_MAN} ${WRKDIR}/daemontools-man/$i.8 ${PREFIX}/man/man8
.endfor

NO_REGRESS=	Yes

.include <bsd.port.mk>
