BROKEN=do not use yet: subject to change without DASH_VER bump
# $MirOS$
# $OpenBSD: Makefile,v 1.11 2013/03/21 08:48:54 ajacoutot Exp $

COMMENT=		manage and configure devices that supports IPMI
DISTNAME=		ipmitool-1.8.11
CATEGORIES=		sysutils
HOMEPAGE=		http://ipmitool.sourceforge.net/

# 3-clause BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=ipmitool/}

SEPARATE_BUILD=		Yes
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOCONF_VERSION=	2.59
AUTOMAKE_VERSION=	1.9
CONFIGURE_ARGS+=	--disable-intf-free
CONFIGURE_ARGS+=	--disable-intf-open
CONFIGURE_ARGS+=	--disable-intf-imb

SHARE_SHEBANG=		bmclanconf collect_data.sh create_rrds.sh \
			create_webpage.sh create_webpage_compact.sh
SHARE_FILES=		ipmi.init.basic ipmi.init.redhat \
			ipmievd.init.debian ipmievd.init.redhat \
			ipmievd.init.suse oem_ibm_sel_map

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/ipmitool/
	${INSTALL_DATA} ${WRKSRC}/contrib/README ${PREFIX}/share/ipmitool/
.for _f in ${SHARE_SHEBANG}
	sed '1s`^.*$$`#!'${MKSH:Q}'`' <${WRKSRC}/contrib/${_f} >${_f}.in
	${INSTALL_SCRIPT} ${_f}.in ${PREFIX}/share/ipmitool/${_f}
.endfor
.for _f in ${SHARE_FILES}
	${INSTALL_SCRIPT} ${WRKSRC}/contrib/${_f} ${PREFIX}/share/ipmitool/
.endfor

.include <bsd.port.mk>
