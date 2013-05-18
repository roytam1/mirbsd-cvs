# $MirOS: ports/lang/pawn/Makefile.inc,v 1.1.1.1 2008/08/08 15:53:57 tg Exp $

CATEGORIES=		lang
HOMEPAGE=		http://www.compuphase.com/pawn/pawn.htm
RESPONSIBLE=		Thorsten Glaser <thorsten.glaser@sygroup.ch>

# zlib
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES+=		http://www.compuphase.com/pawn/

EXTRACT_CASES+=		*.tgz) tar -C ${WRKDIST} \
			    -xzf ${FULLDISTDIR}/$$archive ;;
EXTRACT_CASES+=		*.zip) ${UNZIP} -a -q ${FULLDISTDIR}/$$archive \
			    -d ${WRKDIST} ;;

DESCR=			${.CURDIR}/..
DOCDIR=			${PREFIX}/share/doc/pawn
EXDIR=			${PREFIX}/share/examples/pawn
SHDIR=			${PREFIX}/share/pawn

pre-extract:
	mkdir -p ${WRKSRC}
