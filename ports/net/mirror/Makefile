# $OpenBSD: Makefile,v 1.18 2003/09/22 22:53:37 pvalchev Exp $

COMMENT=			mirror packages on remote sites

DISTNAME=	mirror-2.9
CATEGORIES=	net

MASTER_SITES=	ftp://sunsite.org.uk/packages/mirror/ \
		ftp://ftp.cs.columbia.edu/archives/perl/mirror/ \
		ftp://giswitch.sggw.waw.pl/pub/unix/mirror/  \
		ftp://SunSITE.sut.ac.jp/pub/archives/packages/mirror/

HOMEPAGE=	http://sunsite.org.uk/packages/mirror/

PERMIT_PACKAGE_CDROM=	"may not modify"
PERMIT_PACKAGE_FTP=	"may not modify"
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MAKE_FILE=	makefile

WRKDIST=	${WRKDIR}
NO_REGRESS=	Yes

DOCDIR=		${PREFIX}/share/doc/mirror
DOCS=		copyright.html index.html mirror-faq.html mirror.html \
		mm.html quickstart.html mirror-on-dusk.gif Lake.class

do-configure:
	@-rm -f ${WRKSRC}/mirror.man
	@sed -e 's,@DOCDIR@,${DOCDIR},g' < ${FILESDIR}/mirror.man \
		>${WRKSRC}/mirror.man
	@sed -e 's,@PREFIX@,${PREFIX},g' < ${WRKSRC}/mirror.pl \
		> ${WRKSRC}/mirror
	@sed -e 's,@PREFIX@,${PREFIX},g' < ${WRKSRC}/mm.pl \
		> ${WRKSRC}/mirrormaster

pre-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/mirror

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	@cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${DOCDIR}

.include <bsd.port.mk>
