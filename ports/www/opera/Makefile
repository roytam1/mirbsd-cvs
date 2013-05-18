# $MirOS: ports/www/opera/Makefile,v 1.28 2009/05/25 11:03:15 tg Exp $
# $OpenBSD: Makefile,v 1.31 2005/11/22 21:44:22 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=		fast and customisable WWW browser
VERS=			9.27
DASH_VER=		3
DISTNAME=		opera-${VERS}-20080331.1-static-qt.i386-en
PKGNAME=		opera-${VERS}-${DASH_VER}
CATEGORIES=		www
HOMEPAGE=		http://www.opera.com/
WRKDIST=		${WRKDIR}/${DISTNAME}-709

# Distribution possible under special agreement;
# sublicencing is, however, not allowed.
PERMIT_PACKAGE_CDROM=	"Commercial software"
PERMIT_PACKAGE_FTP=	"Commercial software"
PERMIT_DISTFILES_CDROM=	"Commercial software"
PERMIT_DISTFILES_FTP=	"Commercial software"

EXTRACT_ONLY=		${DISTNAME}${EXTRACT_SUFX}
DISTFILES=		${EXTRACT_ONLY} \
			lux920final.lng:0 \
			Minimalist%20Native.zip:1
OPERA_SKIN_FILES=	Minimalist%20Native.zip
# http://opera-info.de/forum/board.php?boardid=93
OPERA_LANG_FILES=	lux920final.lng

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
	    --prefix=${PREFIX} \
	    --exec_prefix=${PREFIX}/libexec \
	    --plugindir=${PREFIX}/share/opera/plugins
	sed -e 's:@PREFIX@:${TRUEPREFIX}:g' \
	    -e 's:@SHELL@:${MKSH}:g' \
	    -e 's:@LOCALBASE@:${LOCALBASE}:g' \
	    ${FILESDIR}/opera.sh >${PREFIX}/bin/opera
	mv ${PREFIX}/share/doc/opera/* ${PREFIX}/share/opera/
	rmdir ${PREFIX}/share/doc/opera
	for f in ${PREFIX}/share/opera/ini/pluginpath.ini \
	    ${PREFIX}/share/opera/java/opera.policy; do \
		print '%g!${PREFIX}!s!!${TRUEPREFIX}!g\nwq' | \
		    ed -s $$f; \
	done
	print '/^.usr.lib.opera.plugins/s!!${TRUEPREFIX}/share/opera/plugins!\nwq' | \
	    ed -s ${PREFIX}/share/opera/ini/pluginpath.ini
	sed -e 's:@PREFIX@:${TRUEPREFIX}:g' ${FILESDIR}/pluginpaths \
	    >>${PREFIX}/share/opera/ini/pluginpath.ini
	cd ${FULLDISTDIR}; cp ${OPERA_LANG_FILES} ${PREFIX}/share/opera/locale/
	cd ${FULLDISTDIR}; cp ${OPERA_SKIN_FILES} ${PREFIX}/share/opera/skin/

.include <bsd.port.mk>
