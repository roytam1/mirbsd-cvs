# $MirOS: ports/mailnews/mutt/Makefile.inc,v 1.3 2007/03/19 15:19:14 tg Exp $
# $OpenBSD: Makefile.inc,v 1.3 2004/04/06 12:43:46 brad Exp $

DISTNAME=		mutt-${VERSION}i
CATEGORIES=		mail
MASTER_SITES_MUTT=	ftp://ftp.fu-berlin.de/pub/unix/mail/mutt/ \
			ftp://ftp.mutt.org/mutt/ \
			ftp://ftp.gbnet.net/pub/mutt-international/ \
			ftp://ftp.gwdg.de/pub/unix/mail/mutt/international/
MASTER_SITES0=		http://www.spinnaker.de/mutt/compressed/
HOMEPAGE=		http://www.mutt.org/

MODULES=		devel/gettext

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		slang mixmaster compressed
FLAVOUR?=

CONFIGURE_STYLE=	autoconf old
CONFIGURE_ARGS+=	--with-sharedir=${PREFIX:Q}/share/mutt \
			--with-docdir=${PREFIX:Q}/share/doc/mutt \
			--enable-flock \
			--disable-fcntl \
			--enable-external_dotlock \
			--enable-imap \
			--enable-pop \
			--with-ssl \
			--without-gss \
			--sysconfdir=${CONFDIR:Q}
CONFIGURE_ENV+=		ISPELL=${LOCALBASE:Q}/bin/ispell

.if ${FLAVOUR:L:Mslang}
LIB_DEPENDS+=		slang.14::devel/libslang
CONFIGURE_ARGS+=	--with-slang=${PREFIX:Q}
.else
CONFIGURE_ARGS+=	--with-curses
.endif

# compressed folder support provided by
# http://www.spinnaker.de/mutt/compressed/
.if ${FLAVOUR:L:Mcompressed}
PATCHFILES+=		patch-${VERSION}.rr.compressed.1.gz:0
PATCH_DIST_STRIP=	-p1
CONFIGURE_ARGS+=	--enable-compressed
CONFIGURE_STYLE+=	automake
.else
SUPDISTFILES+=		patch-${VERSION}.rr.compressed.1.gz:0
.endif

.if ${FLAVOUR:L:Mmixmaster}
CONFIGURE_ARGS+=	--with-mixmaster=${LOCALBASE:Q}/sbin/mixmaster
RUN_DEPENDS+=		::mail/mixmaster
.endif

.if defined(HOMESPOOL)
CONFIGURE_ARGS+=	--with-homespool=${HOMESPOOL:Q}
.endif

.if defined(DOMAIN)
CONFIGURE_ARGS+=	--with-domain=${DOMAIN:Q}
.endif

WRKDIST=		${WRKDIR}/${DISTNAME:S/i$//}
CONFDIR=		${SYSCONFDIR}/mutt
SUBST_VARS=		CONFDIR

post-install:
	strip ${PREFIX}/bin/mutt
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mutt
	${INSTALL_DATA} ${WRKSRC}/Muttrc \
		${PREFIX}/share/examples/mutt/Muttrc.sample
	${INSTALL_DATA} ${WRKSRC}/mime.types \
		${PREFIX}/share/examples/mutt/mime.types.sample
	mv -f ${PREFIX}/share/doc/mutt/samples/* ${PREFIX}/share/examples/mutt/
	print '%g!/etc/Muttrc!s!!${CONFDIR}/Muttrc!g' \
	    '\n%g!/etc/mime.types!s!!${CONFDIR}/mime.types!g\nwq' | \
	    ed -s ${PREFIX}/man/man1/mutt.1