# $MirOS: ports/www/opera/Makefile,v 1.17 2006/09/21 14:37:31 tg Exp $
# $OpenBSD: Makefile,v 1.31 2005/11/22 21:44:22 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=		fast and customisable WWW browser
VERS=			9.10
DISTNAME=		opera-${VERS}-20061214.1-static-qt.i386-en
PKGNAME=		opera-${VERS}-0
CATEGORIES=		www
HOMEPAGE=		http://www.opera.com/
WRKDIST=		${WRKDIR}/${DISTNAME}-521

# Distribution possible under special agreement;
# sublicencing is, however, not allowed.
PERMIT_PACKAGE_CDROM=	"Commercial software"
PERMIT_PACKAGE_FTP=	"Commercial software"
PERMIT_DISTFILES_CDROM=	"Commercial software"
PERMIT_DISTFILES_FTP=	"Commercial software"

EXTRACT_ONLY=		${DISTNAME}${EXTRACT_SUFX}
DISTFILES=		${EXTRACT_ONLY} \
			lux910final.lng:0 \
			Minimalist%20Native.zip:1
OPERA_LANG_FILES=	lux910final.lng
OPERA_SKIN_FILES=	Minimalist%20Native.zip

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

DBL_FILES=		${PREFIX}/libexec/opera ${PREFIX}/libexec/works \
			${PREFIX}/share/opera/plugins/operaplugincleaner \
			${PREFIX}/share/opera/plugins/operapluginwrapper

do-install:
	cd ${WRKBUILD} && ${SHELL} ./install.sh \
	    --prefix=${PREFIX} \
	    --exec_prefix=${PREFIX}/libexec \
	    --plugindir=${PREFIX}/share/opera/plugins
	chmod 600 ${PREFIX}/libexec/opera
.for _i in ${DBL_FILES}
	perl -i -pe 's!/lib/ld-linux\.so\.2!/dbl/ld-linux.so.2!' ${_i}
.endfor
	chmod ${BINMODE} ${PREFIX}/libexec/opera
	sed -e 's:@PREFIX@:${TRUEPREFIX}:g' \
	    -e 's:@SHELL@:${MKSH}:g' \
	    -e 's:@LOCALBASE@:${LOCALBASE}:g' \
	    ${FILESDIR}/opera.sh >${PREFIX}/bin/opera
	mv ${PREFIX}/share/doc/opera/* ${PREFIX}/share/opera/
	rmdir ${PREFIX}/share/doc/opera
	for f in ${PREFIX}/share/opera/ini/pluginpath.ini \
	    ${PREFIX}/share/opera/java/opera.policy; do \
		print '%g!${PREFIX}!s!!${TRUEPREFIX}!g\nwq' \
		    | ed -s $$f; \
	done
	print '/^.usr.lib.opera.plugins/s!!${TRUEPREFIX}/share/opera/plugins!\nwq' \
	    | ed -s ${PREFIX}/share/opera/ini/pluginpath.ini
	cd ${FULLDISTDIR}; cp ${OPERA_LANG_FILES} ${PREFIX}/share/opera/locale/
	cd ${FULLDISTDIR}; cp ${OPERA_SKIN_FILES} ${PREFIX}/share/opera/skin/

.include <bsd.port.mk>
