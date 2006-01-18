# $MirOS: ports/www/opera/Makefile,v 1.5 2005/12/16 14:42:58 tg Exp $
# $OpenBSD: Makefile,v 1.31 2005/11/22 21:44:22 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=		"fast and customizable WWW browser"
DISTNAME=		opera-8.51-20051114.1-static-qt.i386-en
PKGNAME=		opera-8.51-1
CATEGORIES=		www
HOMEPAGE=		http://www.opera.com/

PERMIT_PACKAGE_CDROM=	"Commercial software"
PERMIT_PACKAGE_FTP=	"Commercial software"
PERMIT_DISTFILES_CDROM=	"Commercial software"
PERMIT_DISTFILES_FTP=	"Commercial software"

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

MASTER_SITES=		${MASTER_SITES_OPERA:=linux/851/final/en/i386/}
EXTRACT_SUFX=		.tar.bz2

RUN_DEPENDS=		:debian-libs-*:emulators/debian

NO_BUILD=		Yes
NO_REGRESS=		Yes

do-install:
	cd ${WRKBUILD} && ${SHELL} ./install.sh \
	    --prefix=${PREFIX} \
	    --exec_prefix=${PREFIX}/libexec \
	    --plugindir=${PREFIX}/lib/opera/plugins
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

.include <bsd.port.mk>
