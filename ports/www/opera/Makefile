# $MirOS: ports/www/opera/Makefile,v 1.8 2006/02/01 20:38:49 tg Exp $
# $OpenBSD: Makefile,v 1.31 2005/11/22 21:44:22 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=		"fast and customizable WWW browser"
VERS=			8.52
DISTNAME=		opera-${VERS}-20060201.1-static-qt.i386-en
PKGNAME=		opera-${VERS}-0
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

MASTER_SITES=		${MASTER_SITES_OPERA:=linux/${VERS:S/.//}/final/en/i386/static/}

RUN_DEPENDS=		:debian-libs->=3.1-1:emulators/debian

NO_BUILD=		Yes
NO_REGRESS=		Yes

do-install:
	cd ${WRKBUILD} && ${SHELL} ./install.sh \
	    --prefix=${PREFIX} \
	    --exec_prefix=${PREFIX}/libexec \
	    --plugindir=${PREFIX}/lib/opera/plugins
	chmod 600 ${PREFIX}/libexec/opera
	perl -i -pe 's!/lib/ld-linux\.so\.2!/dbl/ld-linux.so.2!' \
	    ${PREFIX}/libexec/opera
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

.include <bsd.port.mk>
