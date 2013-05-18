# $MirOS: ports/net/samba/Makefile,v 1.3 2006/01/01 03:49:12 tg Exp $
# $OpenBSD: Makefile,v 1.21 2003/10/26 09:33:23 sturm Exp $

BROKEN=		does not function correctly sometimes

COMMENT=	"SMB and CIFS client and server for UNIX"
COMMENT-docs=	"documentation and examples for samba"

PKGNAME=	${DISTNAME}-0
PKGNAME-docs=	samba-docs-${VERSION}-0

VERSION=	3.0.11
DISTNAME=	samba-${VERSION}
CATEGORIES=	net
HOMEPAGE=	http://www.samba.org/
MASTER_SITES=	\
		http://ca.samba.org/samba/ftp/old-versions/ \
		http://us2.samba.org/samba/ftp/old-versions/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES=	converters/libiconv
S_LIB_DEPENDS=	popt::devel/popt \
		readline::devel/libreadline
MAKE_FLAGS=	PASSWD_PROGRAM="/usr/bin/passwd"
FAKE_FLAGS=	DESTDIR='${WRKINST}' \
		prefix="${PREFIX}" \
		BASEDIR="${PREFIX}" \
		LIBDIR="${PREFIX}/lib/samba" \
		PIDDIR="/var/run" \
		SWATDIR="${PREFIX}/share/swat" \
		SBINDIR="${PREFIX}/libexec" \
		VARDIR="/var"

CONFDIR=	${SYSCONFDIR}/samba
SAMBA_LOGDIR=	/var/log
SUBST_VARS=	CONFDIR

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS=	--libdir="${PREFIX}/lib/samba" \
		--localstatedir="/var" \
		--sbindir="${PREFIX}/libexec" \
		--with-configdir="${CONFDIR}" \
		--with-lockdir="/var/spool/samba" \
		--with-piddir="/var/run" \
		--with-logfilebase="${SAMBA_LOGDIR}" \
		--with-privatedir="${CONFDIR}" \
		--with-readline \
		--with-libsmbclient \
		--with-quotas \
		--with-swatdir="${PREFIX}/share/swat" \
		--with-ssl \
		--with-sslinc="/usr/include/ssl" \
		--with-ssllib="/usr/lib"

FLAVORS=	ads cups ldap
FLAVOR?=

MULTI_PACKAGES=	-docs
SUBPACKAGE?=

.if ${FLAVOR:L:Mads}
.  if ${OSname} == "openbsd"
CPPFLAGS+=	-I/usr/include/kerberosV
FLAVORS+=	ldap
CONFIGURE_ARGS+=--with-ads
.  else
ERRORS+=	Kerberos is not supported on MirOS BSD.
.  endif
.else
CONFIGURE_ARGS+=--without-ads
.endif

.if ${FLAVOR:L:Mcups}
CONFIGURE_ARGS+=--enable-cups
S_LIB_DEPENDS+=	cups::print/cups
.else
CONFIGURE_ARGS+=--disable-cups
.endif

.if ${FLAVOR:L:Mldap}
CONFIGURE_ARGS+=--with-ldap
S_LIB_DEPENDS+=	ldap,lber::databases/openldap
.else
CONFIGURE_ARGS+=--without-ldap
.endif

.if defined(PACKAGING) && ${SUBPACKAGE} == "-docs"
RUN_DEPENDS=	:samba-=${VERSION}:net/samba
.else
LIB_DEPENDS=	${S_LIB_DEPENDS}
.endif

NO_REGRESS=	Yes

WRKDIST=	${WRKDIR}/${DISTNAME}/source

SAMBA_DOCS=	${WRKSRC}/../README \
		${WRKSRC}/../docs/THANKS \
		${WRKSRC}/../docs/history \
		${WRKSRC}/../docs/registry/*.reg

SAMPLE_CONFIG=	${PREFIX}/share/examples/samba/smb.conf.default

.if ${FLAVOR} != ""
pre-extract:
	@echo ">>> Warning: flavoured build not tested!"
	@sleep 3
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/samba/pdf
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/samba/htmldocs
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/samba
	@cp -R ${WRKSRC}/../examples/* ${PREFIX}/share/examples/samba
	@chown -R ${SHAREOWN}:${SHAREGRP} ${PREFIX}/share/examples/samba
	${INSTALL_DATA} ${FILESDIR}/README.MirPorts ${PREFIX}/share/doc/samba
	@for i in ${SAMBA_DOCS}; do \
	 ${INSTALL_DATA} $$i ${PREFIX}/share/doc/samba ;	\
	done
	@for i in ${WRKSRC}/../docs/*.pdf ; do \
	 ${INSTALL_DATA} $$i ${PREFIX}/share/doc/samba/pdf ; \
	done
	@for i in ${WRKSRC}/../docs/htmldocs/* ; do \
	 if [ -f $$i ]; then \
	  ${INSTALL_DATA} $$i ${PREFIX}/share/doc/samba/htmldocs ;\
	 fi \
	done
	@sed -e 's:/usr/spool/samba:/var/spool/samba:g' \
	 -e 's:/usr/local/samba/var/log:${SAMBA_LOGDIR}/smbd:g' \
	 ${WRKSRC}/../examples/smb.conf.default > ${SAMPLE_CONFIG}
	${INSTALL_SCRIPT} ${WRKSRC}/script/mksmbpasswd.sh \
	 ${PREFIX}/bin/mksmbpasswd
	@chown ${BINOWN}:${BINGRP} ${PREFIX}/bin/smbpasswd
	@chmod 111 ${PREFIX}/bin/smbpasswd

.include <bsd.port.mk>
