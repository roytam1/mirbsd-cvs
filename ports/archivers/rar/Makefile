# $MirOS: ports/archivers/rar/Makefile,v 1.4 2005/07/07 21:17:02 bsiegert Exp $
# $OpenBSD: Makefile,v 1.37 2003/10/18 18:20:40 sturm Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386
EMUL=			bsdos

COMMENT=			RAR archiver (BSD/OS binary port)
DISTNAME=		rar-2.0x
DISTFILES=		rarbsd.sfx
PKGNAME=		rar-2.02-1
SUPDISTFILES=		rarsparc.sfx rarbsd.sfx
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>
CATEGORIES=		archivers
MASTER_SITES=		${HOMEPAGE}/rar/ \
			ftp://ftp.netlab.sk/public/rarsoft/rar/

EXTRACT_CASES=		*.sfx) ${SUDO} chmod a+x ${FULLDISTDIR}/$$archive && \
			${FULLDISTDIR}/$$archive;;

HOMEPAGE=		http://www.rarsoft.com/

# Restrictive
PERMIT_PACKAGE_CDROM=	"Shareware.  Requires registration."
PERMIT_PACKAGE_FTP=	"Shareware.  Requires registration."
PERMIT_DISTFILES_CDROM=	"Shareware.  Requires registration."
PERMIT_DISTFILES_FTP=	Yes

NO_BUILD=		Yes
WRKDIST=		${WRKDIR}
SUBST_VARS+=		EMUL

post-extract:
.if ${MACHINE_ARCH} == "sparc"
	@cd ${WRKSRC} && \
	mv RAR rar && mv UNRAR unrar && \
	mv DEFAULT.SFX default.sfx && mv Rar_FAQ.Txt Rar_FAQ.txt
.endif

DOCS=			Rar_FAQ.txt TechNote.Txt License.Txt \
			Internet.Txt Rar.Txt

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/rar
	${INSTALL_DATA_DIR} ${PREFIX}/share/rar
	${INSTALL_PROGRAM} ${WRKSRC}/rar ${PREFIX}/bin/rar
	cd ${WRKSRC}; ${INSTALL_MAN} ${DOCS} ${PREFIX}/share/doc/rar
	${INSTALL_DATA} ${WRKSRC}/RarFiles.Lst ${PREFIX}/share/rar/rarfiles.lst
	${INSTALL_DATA} ${WRKSRC}/default.sfx ${PREFIX}/share/rar
	${INSTALL_DATA} ${WRKSRC}/Dos.SFX ${PREFIX}/share/rar/dos.sfx

NO_REGRESS=		Yes

.include <bsd.port.mk>
