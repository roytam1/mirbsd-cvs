# $MirOS: ports/www/opera/Makefile,v 1.26.2.2 2008/07/09 16:32:30 tg Exp $
# $OpenBSD: Makefile,v 1.52 2008/07/04 06:32:27 sturm Exp $

ONLY_FOR_PLATFORM=	*BSD:*:i386
EMUL=			linux

COMMENT=		fast and customisable WWW browser
VERS=			9.61
OPERA_BUILD=		2456
OPERA_ARCH=		gcc4-static-qt3.i386
DISTNAME=		opera-${VERS}.${OPERA_ARCH}
PKGNAME=		opera-${VERS}-${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.opera.com/
WRKDIST=		${WRKDIR}/opera-${VERS}-${OPERA_BUILD}.${OPERA_ARCH}

# Distribution possible under special agreement;
# sublicencing is, however, not allowed.
PERMIT_PACKAGE_CDROM=	"Commercial software"
PERMIT_PACKAGE_FTP=	"Commercial software"
PERMIT_DISTFILES_CDROM=	"Commercial software"
PERMIT_DISTFILES_FTP=	"Commercial software"

EXTRACT_ONLY=		${DISTNAME}${EXTRACT_SUFX}
DISTFILES=		${EXTRACT_ONLY} \
			lux960final.lng:0 \
			Minimalist%20Native.zip:1
OPERA_SKIN_FILES=	Minimalist%20Native.zip Minimalist\ Native.zip
# http://opera-info.de/forum/board.php?boardid=93
OPERA_LANG_FILES=	lux960final.lng lux960final.lng

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

RUN_DEPENDS=		::emulators/fedora

NO_BUILD=		Yes
NO_REGRESS=		Yes

do-install:
	cd ${WRKBUILD} && ${SHELL} ./install.sh \
	    --DESTDIR=${WRKINST:Q} \
	    --prefix=${TRUEPREFIX:Q} \
	    --exec_prefix=${TRUEPREFIX:Q}/libexec \
	    --docdir=${TRUEPREFIX:Q}/share/doc/opera \
	    --mandir=${TRUEPREFIX:Q}/man \
	    --wrapperdir=${TRUEPREFIX:Q}/bin \
	    --sharedir=${TRUEPREFIX:Q}/share/opera \
	    --plugindir=${TRUEPREFIX:Q}/share/opera/plugins
	print ',g/@LOCALBASE@/s'${LOCALBASE:Q}'g\nwq' | \
	    ed -s ${PREFIX}/bin/opera
	print ',g^/usr/locals^/usr/local\(.*\)$$&\\\n'${TRUEPREFIX:Q}'\\1\nwq' | \
	    ed -s ${PREFIX}/share/opera/ini/pluginpath.ini
.for _s _d in ${OPERA_LANG_FILES}
	cp ${FULLDISTDIR}/${_s} ${PREFIX}/share/opera/locale/${_d}
.endfor
.for _s _d in ${OPERA_SKIN_FILES}
	cp ${FULLDISTDIR}/${_s} ${PREFIX}/share/opera/skin/${_d}
.endfor

.include <bsd.port.mk>
