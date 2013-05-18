# $MirOS$
# $OpenBSD: Makefile,v 1.34 2007/09/15 23:54:16 merdely Exp $

COMMENT=	network-capable tape backup (client and tape server)
COMMENT-client=	network-capable tape backup (client only)
COMMENT-doc=	network-capable tape backup (documentation)

DISTVERSION=	2.4.5p1

PKGVERSION=   ${DISTVERSION:S/p/./}

DISTNAME=	amanda-${DISTVERSION}

PKGNAME=	amanda-${PKGVERSION}-${DASH_VER}
PKGNAME-client=	amanda-client-${PKGVERSION}-${DASH_VER}
PKGNAME-doc=	amanda-doc-${PKGVERSION}-${DASH_VER}

CATEGORIES=	misc

HOMEPAGE=	http://www.amanda.org/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=amanda/}

# AMANDA configure looks for gtar and smbclient so that it can hard-code
# the pathnames.
# Configure looks for gnuplot to see if it should build amplot.
BUILD_DEPENDS+= ::archivers/gtar \
		::math/gnuplot
#		:samba-*:net/samba

# There is no need to set RUN_DEPENDS, because AMANDA will run fine
# without gtar, smbclient, and gnuplot.  They will only be required
# if the user creates a configuration that needs them, and then
# AMANDA will gracefully tell them what is required.

MULTI_PACKAGES=	-client -doc

FLAVOURS=	db gpg
FLAVOUR?=

CONFIGURE_STYLE=		autogen
AUTOCONF_NEW=			Yes
AUTOMAKE_VERSION=		1.9

# Because AMANDA does not conform to shared library naming standards,
# and knowing that no software outside of AMANDA attempts to use the
# shared libraries, we disable the generation of shared libraries.
CONFIGURE_ARGS=	--disable-shared \
		--libexecdir=${PREFIX}/libexec/amanda \
		--localstatedir=/var \
		--with-configdir=${SYSCONFDIR}/amanda \
		--with-user=operator \
		--with-group=operator

# Use this flavor to speed things up if you have large AMANDA
# databases.
.if ${FLAVOUR:L:Mdb}
BUILD_DEPENDS+=  ::databases/db
CONFIGURE_ARGS+= --with-db=db
CFLAGS+=	 -L${LOCALBASE}/lib
.endif

.if ${FLAVOUR:L:Mgpg}
BUILD_DEPENDS+=  :gnupg-*:security/gnupg
CONFIGURE_ENV+=  GZIP=${LOCALBASE}/bin/gpgzip
.endif

OLD_DOC_DIR=	${PREFIX}/share/amanda
DOC_DIR=	${PREFIX}/share/doc/amanda
EXAMPLE_DIR=	${PREFIX}/share/examples/amanda

post-install:
	@cd ${WRKSRC}; \
	  ${INSTALL_DATA_DIR} ${DOC_DIR}; \
	  ${INSTALL_DATA} AUTHORS ${DOC_DIR}; \
	  ${INSTALL_DATA} NEWS ${DOC_DIR}; \
	  ${INSTALL_DATA} README ${DOC_DIR}; \
	  ${INSTALL_DATA} ChangeLog ${DOC_DIR}; \
	  mv ${OLD_DOC_DIR}/* ${DOC_DIR}; \
	  rmdir ${OLD_DOC_DIR}; \
	  ${INSTALL_DATA_DIR} ${EXAMPLE_DIR}; \
	  ${INSTALL_DATA} example/*.ps ${EXAMPLE_DIR}; \
	  ${INSTALL_DATA} example/disklist ${EXAMPLE_DIR}; \
	  cd example; \
	    for f in *.conf *.conf.chg-scsi; do \
	      sed -e 's,usr/adm,var,' \
		  -e 's,/usr/local/etc,${SYSCONFDIR},' $$f \
	      > ${EXAMPLE_DIR}/$$f; \
	    done
	@sed -e 's,@LOCALBASE@,${LOCALBASE},' \
	  ${FILESDIR}/crontab.sample > ${EXAMPLE_DIR}/crontab.sample
	@${INSTALL_DATA} /dev/null ${EXAMPLE_DIR}/amandates
	@sed -e 's,@LOCALBASE@,${LOCALBASE},' \
	     -e 's,@SYSCONFDIR@,${SYSCONFDIR},' \
	     ${FILESDIR}/gpgzip > ${PREFIX}/bin/gpgzip;

.include <bsd.port.mk>
