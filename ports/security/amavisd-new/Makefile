# $MirOS: ports/security/amavisd-new/Makefile,v 1.2 2006/01/01 05:25:30 tg Exp $

BROKEN=			this one uses _foo users but mailnews/amavisd-news is newer - why 2 ports?

COMMENT=			interface between mailer and content checkers
VERSION=		20030616-p6
DISTNAME=		amavisd-new-${VERSION}
PKGNAME=		amavisd-new-${VERSION:S/-/./}-0
WRKDIST=		${WRKDIR}/amavisd-new-${VERSION}
CATEGORIES=		security
HOMEPAGE=		http://www.ijs.si/software/amavisd/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.ijs.si/software/amavisd/ \
			http://mirrors.catpipe.net/amavisd-new/ \
			http://ftp.cfu.net/pub/amavisd-new/

AMAVISUSER=		_amavisd
AMAVISGROUP=		_mailscan

SUBST_VARS=		AMAVISUSER AMAVISGROUP

NO_BUILD=		Yes

RUN_DEPENDS= 		::sysutils/p5-Unix-Syslog \
			::mailnews/p5-Mail-SpamAssassin \
			::mailnews/p5-Mail-Tools \
			::devel/p5-Net-Server \
			::converters/p5-Convert-UUlib \
			::converters/p5-Convert-TNEF \
			::archivers/p5-Archive-Tar \
			::archivers/p5-Archive-Zip \
			::mailnews/p5-MIME-tools \
			::security/clamav


do-install:
	cp ${WRKSRC}/amavisd ${PREFIX}/libexec/
	mkdir ${PREFIX}/share/doc/amavisd-new
	cp ${WRKSRC}/README_FILES/* ${PREFIX}/share/doc/amavisd-new
	cp ${WRKSRC}/{INSTALL,RELEASE_NOTES,LICENSE,LDAP.schema,AAAREADME.first} ${PREFIX}/share/doc/amavisd-new
	mkdir ${PREFIX}/share/examples/amavisd-new
	cp ${WRKSRC}/amavisd.conf ${PREFIX}/share/examples/amavisd-new

.include <bsd.port.mk>
