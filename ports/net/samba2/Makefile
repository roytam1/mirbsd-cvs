# $MirOS: ports/net/samba2/Makefile,v 1.7 2006/12/28 19:21:11 tg Exp $
# $OpenBSD: Makefile,v 1.21 2003/10/26 09:33:23 sturm Exp $

COMMENT=		SMB and CIFS client and server for UNIX
DISTNAME=		samba-2.2.12
DASH_VER=		1
CATEGORIES=		net
MASTER_SITES=		http://us1.samba.org/samba/ftp/old-versions/ \
			http://ca.samba.org/samba/ftp/old-versions/ \
			http://us4.samba.org/samba/ftp/old-versions/
HOMEPAGE=		http://www.samba.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

EXTRA_MAKE_FLAGS+=	PASSWD_PROGRAM=/usr/bin/passwd
EXTRA_FAKE_FLAGS+=	prefix=${WRKINST:Q}${PREFIX:Q} \
			mandir=${WRKINST:Q}${PREFIX:Q}/man \
			MANDIR=${WRKINST:Q}${PREFIX:Q}/man \
			BASEDIR=${WRKINST:Q}${PREFIX:Q} \
			DATADIR=${WRKINST:Q}${PREFIX:Q}/share \
			LIBDIR=${WRKINST:Q}${PREFIX:Q}/lib/samba \
			PIDDIR=${WRKINST:Q}/var/run \
			SWATDIR=${WRKINST:Q}${PREFIX:Q}/share/swat \
			SBINDIR=${WRKINST:Q}${PREFIX:Q}/libexec \
			VARDIR=${WRKINST:Q}/var

CONFDIR=		${SYSCONFDIR}/samba
SAMBA_SPOOL=		/var/spool/samba
SAMBA_LOGDIR=		/var/log
SUBST_VARS+=		SAMBA_SPOOL CONFDIR

LIB_DEPENDS+=		popt::devel/popt \
			readline::devel/libreadline
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	--libdir=${PREFIX:Q}/lib/samba \
			--localstatedir=/var \
			--sbindir=${PREFIX:Q}/libexec \
			--disable-cups \
			--with-configdir=${CONFDIR:Q} \
			--with-lockdir=${SAMBA_SPOOL:Q} \
			--with-piddir=/var/run \
			--with-logfilebase=${SAMBA_LOGDIR:Q} \
			--with-privatedir=${CONFDIR:Q} \
			--with-swatdir=${PREFIX:Q}/share/swat \
			--with-ssl \
			--with-sslinc=/usr/include/ssl \
			--with-ssllib=/usr/lib

NO_REGRESS=		Yes

WRKDIST=		${WRKDIR}/${DISTNAME}/source

SAMBA_DOCS=		${WRKSRC}/../README \
			${WRKSRC}/../WHATSNEW.txt \
			${WRKSRC}/../docs/README.Win2kSP2 \
			${WRKSRC}/../docs/THANKS \
			${WRKSRC}/../docs/history \
			${WRKSRC}/../docs/announce \
			${WRKSRC}/../docs/Registry/*.reg
SAMPLE_CONFIG=		${PREFIX}/share/examples/samba/smb.conf.default

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/samba/faq
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/samba/textdocs
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/samba
	cp -R ${WRKSRC}/../examples/* ${PREFIX}/share/examples/samba/
	chown -R ${SHAREOWN}:${SHAREGRP} ${PREFIX}/share/examples/samba
	${INSTALL_DATA} ${FILESDIR}/README.MirPorts ${PREFIX}/share/doc/samba/
	for i in ${SAMBA_DOCS}; do \
		${INSTALL_DATA} $$i ${PREFIX}/share/doc/samba/;	\
	done
	for i in ${WRKSRC}/../docs/faq/*; do \
		${INSTALL_DATA} $$i ${PREFIX}/share/doc/samba/faq/; \
	done
	for i in ${WRKSRC}/../docs/textdocs/*; do \
		if [[ -f $$i ]]; then \
			${INSTALL_DATA} $$i \
			    ${PREFIX}/share/doc/samba/textdocs/; \
		fi; \
	done
	sed -e 's:/usr/spool/samba:${SAMBA_SPOOL}:g' \
	    -e 's:/usr/local/samba/var/log:${SAMBA_LOGDIR}/smbd:g' \
	    ${WRKSRC}/../examples/smb.conf.default >${SAMPLE_CONFIG}
	${INSTALL_SCRIPT} ${WRKSRC}/script/mksmbpasswd.sh ${PREFIX}/bin/
	${INSTALL_SCRIPT} ${WRKSRC}/script/convert_smbpasswd ${PREFIX}/bin/
	chown ${BINOWN}:${BINGRP} ${PREFIX}/bin/smbpasswd
	chmod 511 ${PREFIX}/bin/smbpasswd

.include <bsd.port.mk>
