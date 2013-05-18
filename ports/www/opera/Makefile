# $MirOS: ports/www/opera/Makefile,v 1.26 2008/04/04 21:35:52 tg Exp $
# $OpenBSD: Makefile,v 1.31 2005/11/22 21:44:22 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=		fast and customisable WWW browser
VERS=			9.50
DISTNAME=		opera-${VERS}.gcc4-static-qt3.i386
PKGNAME=		opera-${VERS}-${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.opera.com/
WRKDIST=		${WRKDIR}/opera-${VERS}-2042.gcc4-static-qt3.i386

# Distribution possible under special agreement;
# sublicencing is, however, not allowed.
PERMIT_PACKAGE_CDROM=	"Commercial software"
PERMIT_PACKAGE_FTP=	"Commercial software"
PERMIT_DISTFILES_CDROM=	"Commercial software"
PERMIT_DISTFILES_FTP=	"Commercial software"

EXTRACT_ONLY=		${DISTNAME}${EXTRACT_SUFX}
DISTFILES=		${EXTRACT_ONLY} \
			lux950beta1.lng:0 \
			Minimalist%20Native.zip:1
OPERA_SKIN_FILES=	Minimalist%20Native.zip
# http://opera-info.de/forum/board.php?boardid=93
OPERA_LANG_FILES=	lux950beta1.lng

MASTER_SITES_OPERA=	ftp://ftp.opera.com/pub/opera/ \
			ftp://gd.tuwien.ac.at/infosys/browsers/opera/ \
			ftp://ftp.hu-berlin.de/pub/www/opera/ \
			ftp://sunsite.cnlab-switch.ch/mirror/opera/ \
			ftp://ftp.planetmirror.com/pub/opera/ \
			ftp://ftp.sunet.se/pub/www/clients/Opera/ \
			ftp://ftp.task.gda.pl/pub/opera/ \
			ftp://opera.mirror.stop.hu/opera/ \
			http://www.panix.com/opera/files/ \
			ftp://ftp.rge.com/pub/infosystems/opera/ \
			http://www.rge.com/pub/infosystems/opera/

MASTER_SITES=		${MASTER_SITES_OPERA:=linux/${VERS:S/.0$/00/:S/.//}/final/en/i386/static/}
MASTER_SITES0=		http://files.opera-info.de/philo/lng/
MASTER_SITES1=		http://opera-fansite.de/files/skins/

RUN_DEPENDS=		:debian-libs->=3.1-2:emulators/debian

NO_BUILD=		Yes
NO_REGRESS=		Yes

DBL_FILES=		${PREFIX}/libexec/opera \
			${PREFIX}/libexec/operaplugincleaner \
			${PREFIX}/libexec/operapluginwrapper

do-install:
	cd ${WRKBUILD} && ${SHELL} ./install.sh \
	    --DESTDIR=${WRKINST:Q} \
	    --prefix=${TRUEPREFIX:Q} \
	    --exec_prefix=${TRUEPREFIX:Q}/libexec \
	    --plugindir=${TRUEPREFIX:Q}/share/opera/plugins
	chmod 600 ${PREFIX}/libexec/opera
.for _i in ${DBL_FILES}
	perl -i -pe 's!/lib/ld-linux\.so\.2!/dbl/ld-linux.so.2!' ${_i}
.endfor
	chmod ${BINMODE} ${PREFIX}/libexec/opera
	rm -rf ${PREFIX}/share/doc/opera
	cd ${FULLDISTDIR} && \
	    cp ${OPERA_LANG_FILES} ${PREFIX}/share/opera/locale/ && \
	    cp ${OPERA_SKIN_FILES} ${PREFIX}/share/opera/skin/

.include <bsd.port.mk>
