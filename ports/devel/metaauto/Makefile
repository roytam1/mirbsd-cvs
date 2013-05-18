# $MirOS: ports/devel/metaauto/Makefile,v 1.1.7.1 2005/03/18 15:44:58 tg Exp $
# $OpenBSD: Makefile,v 1.3 2003/05/22 22:54:05 jcs Exp $

COMMENT=			wrapper for gnu auto*
VERSION=	0.3
DISTNAME=	metaauto-${VERSION}
CATEGORIES=	devel
DISTFILES=

# BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

SCRIPTS1=	autoconf autoheader autom4te autoreconf autoupdate
SCRIPTS2=	aclocal automake
WRKDIST=	${WRKDIR}

do-build:
.for i in ${SCRIPTS1}
	sed -e s,@LOCALBASE@,${LOCALBASE},g -e s,@SCRIPT@,$i,g \
	    -e s,AUTOTOOLS_VERSION,AUTOCONF_VERSION,g \
	    <${FILESDIR}/meta.in >${WRKBUILD}/$i
.endfor
.for i in ${SCRIPTS2}
	sed -e s,@LOCALBASE@,${LOCALBASE},g -e s,@SCRIPT@,$i,g \
	    -e s,AUTOTOOLS_VERSION,AUTOMAKE_VERSION,g \
	    <${FILESDIR}/meta.in >${WRKBUILD}/$i
.endfor

do-install:
.for i in ${SCRIPTS1} ${SCRIPTS2}
	${INSTALL_SCRIPT} ${WRKBUILD}/$i ${PREFIX}/bin
.endfor

.include <bsd.port.mk>
