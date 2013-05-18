# $MirOS: ports/devel/metaauto/Makefile,v 1.2 2006/09/14 00:08:26 tg Exp $
# $OpenBSD: Makefile,v 1.3 2003/05/22 22:54:05 jcs Exp $

COMMENT=		wrapper for GNU auto*
VERSION=		1.0
DISTNAME=		metaauto-${VERSION}
CATEGORIES=		devel
DISTFILES=

# so small it needs none
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

SCRIPTS_CONF=		autoconf autoheader autom4te autoreconf autoupdate
SCRIPTS_MAKE=		aclocal automake
SCRIPTTYPES=		CONF MAKE
WRKDIST=		${WRKDIR}

X_SCRIPTS:=
.for _i in ${SCRIPTTYPES}
X_SCRIPTS+=		${SCRIPTS_${_i}}
.endfor

do-build:
.for _i in ${SCRIPTTYPES}
.  for _j in ${SCRIPTS_${_i}}
	sed \
	    -e s@LOCALBASEQ@${LOCALBASE:Q:Q}g \
	    -e s@SCRIPT@${_j:Q}g \
	    -e sAUTOTOOLSAUTO${_i:Q}g \
	    <${FILESDIR:Q}/meta.in >${WRKBUILD:Q}/${_j:Q}
	sed \
	    -e s@LOCALBASE@${LOCALBASE:Q}g \
	    -e s@SCRIPT@${_j:Q}g \
	    -e sAUTOTOOLSAUTO${_i:Q}g \
	    <${FILESDIR:Q}/man.in >${WRKBUILD:Q}/${_j:Q}.1
.  endfor
.endfor
	cd ${WRKBUILD:Q} && ${MAKE} -f ${.SYSMK}/bsd.man.mk __MANALL \
	    MAN=${X_SCRIPTS:S/$/.1/:Q} MANDIR=${TRUEPREFIX}/man/cat

do-install:
	cd ${WRKBUILD:Q} && ${INSTALL_SCRIPT} ${X_SCRIPTS} ${PREFIX:Q}/bin/
	cd ${WRKBUILD:Q} && ${MAKE} -f ${.SYSMK}/bsd.man.mk maninstall \
	    MAN=${X_SCRIPTS:S/$/.1/:Q} MANDIR=${TRUEPREFIX}/man/cat

.include <bsd.port.mk>
