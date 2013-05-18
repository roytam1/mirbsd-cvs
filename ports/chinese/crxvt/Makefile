# $MirOS: ports/chinese/crxvt/Makefile,v 1.4 2008/10/04 19:03:02 tg Exp $
# $OpenBSD: Makefile,v 1.15 2003/09/22 22:53:36 pvalchev Exp $

COMMENT=			Chinese(Big5) VT100 terminal emulator for X

DISTNAME=       crxvt-2.10-2
PKGNAME=        zh-crxvt-2.10.2-0
CATEGORIES=     chinese 

MASTER_SITES=   ftp://ftp.linux.org.tw/pub/xcin/old/ \
		ftp://ftp.shellhung.org/pub/OpenBSD/packages/chinese/


PERMIT_PACKAGE_CDROM=   "no license"
PERMIT_PACKAGE_FTP=     "no license"
PERMIT_DISTFILES_CDROM= "no license"
PERMIT_DISTFILES_FTP=   "no license"

RUN_DEPENDS=	::chinese/taipeifonts

USE_X11=	Yes

CONFIGURE_STYLE=	gnu old
CONFIGURE_ARGS=	--os=OpenBSD --no-menu

post-configure:
	mv ${WRKSRC}/config.status ${WRKSRC}/config.status.orig
	sed -e '/OPT_CRXVT_CFONT/s/=.*/=-taipei-ming-medium-r-normal--16-160-75-75-c-160-big5-0/' ${WRKSRC}/config.status.orig > ${WRKSRC}/config.status
	
post-extract:
	mv ${FILESDIR}/OpenBSD ${WRKSRC}/script/os_def/
	echo CC=${_PASS_CC:T:Q} >> ${WRKSRC}/script/os_def/OpenBSD
	echo CFLAGS=${CFLAGS:Q} >> ${WRKSRC}/script/os_def/OpenBSD

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/src/crxvt ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/doc/man/crxvt.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
