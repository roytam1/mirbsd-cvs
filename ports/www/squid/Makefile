# $MirOS: ports/www/squid/Makefile,v 1.5 2006/02/09 09:36:20 tg Exp $
# $OpenBSD: Makefile,v 1.61 2004/04/21 11:11:19 brad Exp $

COMMENT=			WWW and FTP proxy cache and accelerator
DISTNAME=	squid-2.5.STABLE10
PKGNAME=	${DISTNAME}-1
CATEGORIES=	www
MASTER_SITES=	${HOMEPAGE}Versions/v2/2.5/
MASTER_SITES0=	${HOMEPAGE}Versions/v2/2.5/bugs/
DIST_SUBDIR=	squid

PATCH_DIST_STRIP= -p1
PATCHFILES=	${DISTNAME}-content_length.patch:0 \
		${DISTNAME}-spanish.patch:0 \
		${DISTNAME}-internal_date.patch:0 \
		${DISTNAME}-chroot-2.patch:0 \
		${DISTNAME}-transparent-2.patch:0 \
		${DISTNAME}-redirect_flags.patch:0 \
		${DISTNAME}-cache_dir_change.patch:0 \
		${DISTNAME}-snmp_getnext.patch:0 \
		${DISTNAME}-ftp_title-2.patch:0 \
		${DISTNAME}-ftp_basehref.patch:0 \
		${DISTNAME}-wbinfo_groups.patch:0 \
		${DISTNAME}-64bit_cleanup.patch:0 \
		${DISTNAME}-wb_ntlm_auth_silent.patch:0 \
		${DISTNAME}-buildenv.patch:0 \
		${DISTNAME}-mail_program.patch:0 \
		${DISTNAME}-arp_ipfilter-2.patch:0 \
		${DISTNAME}-sslConnectTimeout.patch:0 \
		${DISTNAME}-statHistAssert.patch:0 \
		${DISTNAME}-chroot_dir.patch:0 \
		${DISTNAME}-errmsg.patch:0 \
		${DISTNAME}-FORTIFY_SOURCE.patch:0 \
		${DISTNAME}-ftp_250.patch:0 \
		${DISTNAME}-Greek.patch:0 \
		${DISTNAME}-STORE_PENDING.patch:0 \
		${DISTNAME}-ldap_auth-U.patch:0 \
		${DISTNAME}-cacheClientTable.patch:0 \
		${DISTNAME}-Solaris_IPFilter.patch:0 \
		${DISTNAME}-mail_from.patch:0

HOMEPAGE=	http://www.squid-cache.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

SQUIDDIR?=	/var/squid
SUBST_VARS=	SQUIDDIR

FLAVORS=	transparent
FLAVOR?=

CONFIGURE_STYLE= autoconf no-autoheader
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/cfgaux
CONFIGURE_ARGS=	--enable-removal-policies="lru heap" \
		--enable-storeio="ufs diskd" \
		--enable-ssl \
		--datadir="${PREFIX}/share/squid" \
		--localstatedir="${SQUIDDIR}"

.if ${FLAVOR:L:Mtransparent}
CONFIGURE_ARGS+= --enable-pf-transparent
.endif

post-install:
	@chown -R ${SHAREOWN}:${SHAREGRP} ${PREFIX}/share/examples/squid
	@find ${PREFIX}/share/examples/squid/errors \
		-name '*.orig' -print0 | xargs -0 rm -f

.include <bsd.port.mk>
