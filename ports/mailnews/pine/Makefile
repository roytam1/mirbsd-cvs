# $MirOS: ports/mailnews/pine/Makefile,v 1.30 2015/07/19 12:25:43 tg Exp $
# $OpenBSD: Makefile,v 1.56 2003/10/05 21:42:29 jakob Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:* MirBSD:*:*

COMMENT=		program for Internet News and eMail
COMMENT-cclient=	University of Washington c-client mail access routines
COMMENT-daemon=		University of Washington IMAP4rev1/POP2/POP3 mail servers
COMMENT-mailutil=	University of Washington IMAP4rev1/POP2/POP3 mail utility
COMMENT-pico=		small text editor
COMMENT-pilot=		filesystem browser
CATEGORIES=		devel editors mail net news sysutils
VERSION=		4.64
PICO_VERSION=		4.10
PILOT_VERSION=		2.0
IMAP_VERSION=		2004.357
CCLIENT_PATCHLEV=	9
#PINE_PATCHLEV=		9	# must be the highest
PINE_PATCHLEV?=		${CCLIENT_PATCHLEV}
PICOLOT_PATCHLEV=	3
DISTNAME=		pine${VERSION}
PKGNAME=		pine-${VERSION}-${PINE_PATCHLEV}
PKGNAME-cclient=	c-client-${VERSION}-${CCLIENT_PATCHLEV}
PKGNAME-daemon=		imap-uw-${IMAP_VERSION}-${CCLIENT_PATCHLEV}
PKGNAME-mailutil=	mailutil-uw-${IMAP_VERSION}-${CCLIENT_PATCHLEV}
FULLPKGNAME-pico=	pico-${PICO_VERSION}-${PICOLOT_PATCHLEV}
FULLPKGNAME-pilot=	pilot-${PILOT_VERSION}-${PICOLOT_PATCHLEV}
MASTER_SITES=		ftp://ftp.cac.washington.edu/pine/old/ \
			ftp://ftp.sunet.se/pub/unix/mail/pine/old/ \
			ftp://ftp.cac.washington.edu/pine/ \
			ftp://ftp.sunet.se/pub/unix/mail/pine/
EXTRACT_SUFX=		.tar.Z
HOMEPAGE=		http://www.washington.edu/pine/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# Free, but cannot distribute with non-opensource on same media.
# Modified versions must be marked as such.
PERMIT_PACKAGE_CDROM=	"restricts mere aggregation"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"restricts mere aggregation"
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=		Yes

FLAVOURS=		ldap plaintext
FLAVOUR?=

.include <mirports.sys.mk>

MULTI_PACKAGES=		-cclient -daemon -mailutil -pico -pilot
SUBPACKAGE?=

PINE_BUILD_FLAGS=	CC=${_PASS_CC:T:Q} EXTRACFLAGS=${CFLAGS:Q} \
			LOCALBASE="${LOCALBASE}" PICFLAG="${PICFLAG}"
.if defined(NO_SHARED_LIBS) && ${NO_SHARED_LIBS:L} == "yes"
PINE_BUILD_FLAGS+=	NO_SHARED_LIBS=yes
.endif

.if ${FLAVOUR:L:Mldap}
PINE_BUILD_FLAGS+=	LDAPLIBS="-L${LOCALBASE}/lib -lldap -llber" \
			LDAPCFLAGS="-DENABLE_LDAP -I${LOCALBASE}/include"
.  if ${SUBPACKAGE} != "-pico" && ${SUBPACKAGE} != "-pilot"
LIB_DEPENDS+=		ldap.2:openldap-client-2.*:databases/openldap
.  endif
.endif

.if ${FLAVOUR:L:Mplaintext}
PINE_BUILD_FLAGS+=	SSLTYPE="unix"
.else
PINE_BUILD_FLAGS+=	SSLTYPE="unix.nopwd"
.endif

IMAP_DOCFILES=		../CPYRIGHT FAQ.html FAQ.txt RELNOTES Y2K bugs.txt \
			calendar.txt commndmt.txt drivers.txt formats.txt \
			imaprc.txt internal.txt locking.txt md5.txt naming.txt

LIB_HEADERS=		c-client.h env.h env_unix.h flstring.h fs.h ftl.h \
			imap4r1.h linkage.c linkage.h mail.h misc.h nl.h \
			nntp.h osdep.h rfc822.h smtp.h tcp.h utf8.h

ATSED=			-e 's!@SHELL@!${SHELL}!g' \
			-e 's!@PREFIX@!${TRUEPREFIX}!g' \
			-e 's!@ETC@!${SYSCONFDIR}!g'
ATSED_DEPS=		build imap/Makefile imap/src/imapd/Makefile \
			imap/src/osdep/unix/Makefile \
			imap/src/osdep/unix/Makefile.md5 \
			imap/src/osdep/unix/env_unix.h \
			pine/osdep/os-bso.h pine/pine.hlp
ATSED_FILES=		doc/pine.1 imap/src/tmail/tmail.1

post-extract:
	@cp ${FILESDIR}/ckp_bso.c ${WRKSRC}/imap/src/osdep/unix/

do-build:
.for _i in pine.smime.init pine.smime dot.pinerc.pgp.sample
	sed ${ATSED} <${FILESDIR}/${_i} >${WRKBUILD}/${_i}
.endfor
	sed ${ATSED} ${WRKSRC}/doc/tech-notes.txt \
	    >${WRKBUILD}/doc/tech-notes.txt.new
.for _i in ${ATSED_DEPS}
	cd ${WRKSRC} && mv ${_i} ${_i}.bak && sed ${ATSED} <${_i}.bak >${_i}
.endfor
	@cd ${WRKSRC} && chmod a+x build && exec ${SETENV} ${MAKE_ENV} \
	    ./build ${PINE_BUILD_FLAGS} bso

do-install:
.for _i in ${ATSED_FILES}
	cd ${WRKSRC} && mv ${_i} ${_i}.bak && sed ${ATSED} <${_i}.bak >${_i}
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/pine
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/imap-uw
	${INSTALL_DATA_DIR} ${PREFIX}/include/c-client
	cd ${WRKSRC}/bin; ${INSTALL_PROGRAM} pico pilot pine \
	    rpdump rpload ${PREFIX}/bin/
	cd ${WRKSRC}/doc; ${INSTALL_MAN} pico.1 pilot.1 pine.1 \
	    rpdump.1 rpload.1 ${PREFIX}/man/man1/
	${INSTALL_PROGRAM} ${WRKSRC}/imap/dmail/dmail ${PREFIX}/libexec
	${INSTALL_PROGRAM} ${WRKSRC}/imap/imapd/imapd ${PREFIX}/libexec
	${INSTALL_PROGRAM} ${WRKSRC}/imap/ipopd/ipop2d ${PREFIX}/libexec
	${INSTALL_PROGRAM} ${WRKSRC}/imap/ipopd/ipop3d ${PREFIX}/libexec
	${INSTALL_PROGRAM} ${WRKSRC}/imap/mailutil/mailutil ${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKSRC}/imap/mlock/mlock ${PREFIX}/libexec
	${INSTALL_PROGRAM} ${WRKSRC}/imap/tmail/tmail ${PREFIX}/libexec
	${INSTALL_MAN} ${WRKSRC}/imap/src/dmail/dmail.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/imap/src/imapd/imapd.8 \
	    ${PREFIX}/man/man8/imapd.8
	${INSTALL_MAN} ${WRKSRC}/imap/src/ipopd/ipopd.8 \
	    ${PREFIX}/man/man8/ipop2d.8
	cd ${PREFIX}/man/man8 && ln ipop2d.8 ipop3d.8
	${INSTALL_MAN} ${WRKSRC}/imap/src/mailutil/mailutil.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/imap/src/tmail/tmail.1 ${PREFIX}/man/man1
.for _i in pgpencrypt pgpdecode pgpsign mbxfix
	${INSTALL_SCRIPT} ${FILESDIR}/${_i} ${PREFIX}/bin/
.endfor
.for _i in pine.smime.init pine.smime
	${INSTALL_SCRIPT} ${WRKBUILD}/${_i} ${PREFIX}/bin/
.endfor
	${INSTALL_DATA} ${WRKBUILD}/dot.pinerc.pgp.sample \
	    ${PREFIX}/share/doc/pine/
	${INSTALL_DATA} ${WRKBUILD}/doc/tech-notes.txt.new \
	    ${PREFIX}/share/doc/pine/tech-notes.txt
	${INSTALL_DATA} ${WRKSRC}/doc/brochure.txt ${WRKSRC}/CPYRIGHT \
	    ${PREFIX}/share/doc/pine/
	cd ${WRKSRC}/imap/docs; ${INSTALL_DATA} ${IMAP_DOCFILES} \
	    ${PREFIX}/share/doc/imap-uw/
	cd ${WRKSRC}/imap/c-client; ${INSTALL_DATA} ${LIB_HEADERS} \
	    ${PREFIX}/include/c-client/
	${INSTALL_DATA} ${WRKSRC}/imap/c-client/c-client.a \
	    ${PREFIX}/lib/libc-client.a
	${INSTALL_DATA} ${WRKSRC}/imap/c-client/c-client_pic.a \
	    ${PREFIX}/lib/libc-client_pic.a

.include <bsd.port.mk>
