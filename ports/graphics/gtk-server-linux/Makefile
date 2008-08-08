# $MirOS$

ONLY_FOR_PLATFORM=	*:*:i386
NOT_FOR_PLATFORM=	Darwin:*:* Interix:*:*
EMUL=			linux

CATEGORIES=		graphics devel
COMMENT=		scripting server for GTK+1 toolkit
DISTNAME=		gtk-server-20080808
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
HOMEPAGE=		http://www.gtk-server.org/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		http://www.gtk-server.org/gtk1/
MASTER_SITES0=		http://www.gtk-server.org/
DISTFILES=		gtk-server.cfg:0 gtk-server.gz
DIST_SUBDIR=		${DISTNAME}

NO_BUILD=		Yes
NO_REGRESS=		Yes

EXTRACT_CASES+=		*.cfg) cp ${FULLDISTDIR}/$$archive . ;;
WRKDIST=		${WRKDIR}

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gtk-server
	${INSTALL_DATA} ${WRKDIST}/gtk-server.cfg \
	    ${PREFIX}/share/examples/gtk-server/
	${INSTALL_SCRIPT} ${WRKDIST}/gtk-server ${PREFIX}/bin/

.include <bsd.port.mk>
