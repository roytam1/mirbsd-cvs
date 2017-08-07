# $MirOS: ports/mailnews/alpine/Makefile,v 1.6 2009/02/02 20:15:46 bsiegert Exp $

ONLY_FOR_PLATFORM=	Darwin:*:*

COMMENT=		programme for Internet News and eMail, curses interface
COMMENT-web=		programme for Internet News and eMail, web interface
COMMENT-cclient=	University of Washington c-client eMail access routines
COMMENT-daemon=		University of Washington IMAP4rev1/POP2/POP3 mail servers
COMMENT-mailutil=	University of Washington eMail management utility
COMMENT-pico=		small text editor embedded in alpine
COMMENT-pilot=		filesystem browser embedded in alpine
CATEGORIES=		devel editors mail mailnews net news sysutils
HOMEPAGE=		http://www.washington.edu/alpine/
VERSION=		2.00
CCLIENT_VERSION=	2007c
PICO_VERSION=		5.04
PILOT_VERSION=		2.99
DASH_VER=		0	# must be the highest out of these
DASH_VER-cclient=	0
DASH_VER-picolot=	0
DISTNAME=		alpine-${VERSION}
PKGNAME-web=		alpine-web-${VERSION}-${DASH_VER}
PKGNAME-cclient=	c-client-${CCLIENT_VERSION}-${DASH_VER-cclient}
PKGNAME-daemon=		imap-uw-${CCLIENT_VERSION}-${DASH_VER-cclient}
PKGNAME-mailutil=	mailutil-uw-${CCLIENT_VERSION}-${DASH_VER-cclient}
FULLPKGNAME-pico=	pico-${PICO_VERSION}-${DASH_VER-picolot}
FULLPKGNAME-pilot=	pilot-${PILOT_VERSION}-${DASH_VER-picolot}
MASTER_SITES=		ftp://ftp.cac.washington.edu/alpine/ \
			ftp://ftp.cac.washington.edu/alpine/old/ \
			ftp://ftp.fu-berlin.de/unix/mail/alpine/ \
			ftp://ftp.fu-berlin.de/unix/mail/alpine/old/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# Apache Licence v2.0
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

FLAVOURS=		ldap
FLAVOUR?=

MULTI_PACKAGES=		-cclient -daemon -mailutil -pico -pilot #-web
SUBPACKAGE?=

# no TCL on Darwin yet
#TCL_VERSION?=		8.4
#BUILD_DEPENDS+=		:tcl-${TCL_VERSION}*:lang/tcl/${TCL_VERSION}

#.if defined(PACKAGING) && (${SUBPACKAGE} == "-web")
#LIB_DEPENDS+=		tcl::lang/tcl/${TCL_VERSION}
#.endif

.if defined(PACKAGING) && (${SUBPACKAGE} != "-cclient") && \
    (${SUBPACKAGE} != "-pico") && (${SUBPACKAGE} != "-pilot")
# no shlib yet
#LIB_DEPENDS+=		c-client::mailnews/alpine,-cclient
.endif

.if ${FLAVOUR:L:Mldap}
BUILD_DEPENDS+=		:openldap-client-*:databases/openldap
.  if defined(PACKAGING) && (${SUBPACKAGE} != "-web") && \
    (${SUBPACKAGE} != "-pico") && (${SUBPACKAGE} != "-pilot")
LIB_DEPENDS+=		ldap::databases/openldap
.  endif
.endif

.if ${OStype} == "Darwin"
ccOStype=		oxp
USE_CA_CERTIFICATES=	Yes
.elif ${OStype} == "Interix"
# untested
ccOStype=		sua
USE_CA_CERTIFICATES=	No		#XXX for now
.elif ${OStype} == "MidnightBSD"
# untested
ccOStype=		bsg
USE_CA_CERTIFICATES=	Yes
.elif ${OStype} == "MirBSD"
# untested
ccOStype=		bsm
USE_CA_CERTIFICATES=	No
.elif ${OStype} == "OpenBSD"
# untested
ccOStype=		bso
USE_CA_CERTIFICATES=	Yes
.endif

CONFIGURE_STYLE=	autoconf detectheader
AUTOCONF_NEW=		Yes
#MODGNU_RECURSE_DIRS=	${WRKSRC}/web/src/cgi.tcl-1.10 ${WRKSRC}
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--with-system-pinerc=${SYSCONFDIR:Q}/pine.conf \
			--with-system-fixed-pinerc=${SYSCONFDIR:Q}/pine.conf.fixed \
			--with-debug-file=.etc/pine-debug \
			--with-default-signature-file=.etc/sig \
			--with-default-addressbook=.etc/addressbook \
			--with-passfile=.etc/ssh/pine.pwd \
			--with-ssl-dir=/usr \
			--with-ssl-certs-dir=/etc/ssl/certs \
			--with-tcl-lib=tcl${TCL_VERSION:S/.//} \
			--with-tcl-include=${LOCALBASE:Q}/include/tcl${TCL_VERSION} \
			--with-c-client-target=${ccOStype} \
			--disable-nls
CONFIGURE_ARGS+=	--without-tcl	#XXX for now

.if ${OStype} == "Interix"
CONFIGURE_ARGS+=	--without-ipv6 \
			--without-ssl	#XXX for now
.endif

.if (${OStype} == "MidnightBSD") || (${OStype} == "OpenBSD")
CONFIGURE_ARGS+=	--with-krb5-dir=/usr
.else
CONFIGURE_ARGS+=	--without-krb5
.endif

.if ${FLAVOUR:L:Mldap}
# untested
CONFIGURE_ARGS+=	--with-ldap-dir=${LOCALBASE:Q}
.else
CONFIGURE_ARGS+=	--without-ldap
.endif

.if ${USE_CA_CERTIFICATES:L} == "yes"
CONFIGURE_ARGS+=	--with-ssl-certs-dir=${LOCALBASE:Q}/share/ca-certificates
BUILD_DEPENDS+=		:ca-certificates-*:essentials/ca-certificates
.  if defined(PACKAGING) && \
    (${SUBPACKAGE} != "-pico") && (${SUBPACKAGE} != "-pilot")
RUN_DEPENDS+=		:ca-certificates-*:essentials/ca-certificates
.  endif
.endif

SUBST_VARS+=		VERSION TCL_VERSION
WEBALPINEDIR=		${PREFIX}/share/${PKGNAME-web}

REPLVARS=		MKSH TRUEPREFIX SYSCONFDIR
REPLDATA=
EXTRASCRIPTS=		mbxfix #pgpencrypt pgpdecode pgpsign \
#			pine.smime pine.smime.init

post-extract:
	cd ${FILESDIR} && pax -vrw . ${WRKSRC}/
	@-rm -f ${WRKDIR}/REPLSCRIPT
.for _i in ${REPLVARS}
	@print ,g@${_i:Q}@s${${_i}:Q}g >>${WRKDIR}/REPLSCRIPT
.endfor
	@print wq >>${WRKDIR}/REPLSCRIPT

pre-build:
.for _f in ${EXTRASCRIPTS} ${REPLDATA}
	cd ${WRKBUILD} && ed -s ${_f:Q} <${WRKDIR}/REPLSCRIPT
.endfor

#post-build:
#	cd ${WRKBUILD}/web/src && exec ${_SYSTRACE_CMD} ${SETENV} ${MAKE_ENV} \
#	    ${MAKE_PROGRAM} ${MAKE_FLAGS} -f ${MAKE_FILE} ${ALL_TARGET}

post-install:
#	cd ${WRKBUILD}/web/src && exec ${SUDO} ${_SYSTRACE_CMD} \
#	    ${SETENV} ${MAKE_ENV} ${_FAKE_SETUP} \
#	    ${MAKE_PROGRAM} ${FAKE_FLAGS} -f ${MAKE_FILE} ${FAKE_TARGET}
#	${INSTALL_DATA_DIR} ${WEBALPINEDIR}
#	cd ${WRKBUILD}/web/src && pax -rw . ${WEBALPINEDIR}/
#	rm -rf ${WEBALPINEDIR}/src
	${INSTALL_DATA_DIR} ${PREFIX}/include/c-client \
	    ${PREFIX}/share/doc/{alpine,c-client}
	cd ${WRKSRC}/imap && \
	    ${INSTALL_PROGRAM} dmail/dmail imapd/imapd ipopd/ipop2d \
	    ipopd/ipop3d mailutil/mailutil mlock/mlock tmail/tmail \
	    ${PREFIX}/libexec/ && \
	    cd src && \
	    ${INSTALL_MAN} dmail/dmail.1 mailutil/mailutil.1 tmail/tmail.1 \
	    ${PREFIX}/man/man1/ && \
	    ${INSTALL_MAN} imapd/imapd.8 ipopd/ipopd.8 ${PREFIX}/man/man8/
	mv ${PREFIX}/libexec/mailutil ${PREFIX}/bin/
	cd ${PREFIX}/man/man8 && mv ipopd.8 ipop2d.8 && ln ipop2d.8 ipop3d.8
	${INSTALL_DATA} ${WRKSRC}/{NOTICE,README} \
	    ${WRKSRC}/doc/{brochure,tech-notes}.txt ${PREFIX}/share/doc/alpine/
	cd ${WRKSRC}/imap/docs && ${INSTALL_DATA} \
	    ../{LICENSE.txt,NOTICE,README,SUPPORT} CONFIG FAQ.html FAQ.txt \
	    IPv6.txt RELNOTES SSLBUILD Y2K FAQ.txt IPv6.txt bugs.txt \
	    calendar.txt commndmt.txt drivers.txt formats.txt imaprc.txt \
	    internal.txt locking.txt md5.txt mixfmt.txt naming.txt \
	    ${PREFIX}/share/doc/c-client/
	cd ${WRKSRC}/imap/c-client && ${INSTALL_DATA} c-client.h dummy.h \
	    env.h env_unix.h fdstring.h flstring.h fs.h ftl.h imap4r1.h \
	    linkage.h mail.h misc.h netmsg.h newsrc.h nl.h nntp.h osdep.h \
	    pseudo.h rfc822.h smtp.h sslio.h tcp.h tcp_unix.h unix.h utf8.h \
	    utf8aux.h ${PREFIX}/include/c-client/
	${INSTALL_DATA} ${WRKBUILD}/imap/c-client/c-client.a \
	    ${PREFIX}/lib/libc-client.a
	cd ${WRKBUILD} && ${INSTALL_SCRIPT} ${EXTRASCRIPTS} ${PREFIX}/bin/

.include <bsd.port.mk>
