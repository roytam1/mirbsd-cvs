BROKEN=do not use yet: subject to change without DASH_VER bump
# $MirOS$
# $OpenBSD: Makefile,v 1.16 2013/03/21 08:48:53 ajacoutot Exp $

# needs machine/sysarch.h & machine/pio.h
ONLY_FOR_PLATFORM+=	MirBSD:*:i386
ONLY_FOR_PLATFORM+=	OpenBSD:*:amd64 OpenBSD:*:arm OpenBSD:*:i386

COMMENT=		FreeIPMI provides in-band and out-of-band IPMI software
VSN=			0.4.6
DISTNAME=		freeipmi-${VSN}
CATEGORIES=		sysutils
HOMEPAGE=		http://www.gnu.org/software/freeipmi/
MASTER_SITES=		ftp://ftp.zresearch.com/pub/freeipmi/${VSN}/

# GNU GPLv2+
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		devel/gettext
BUILD_DEPENDS+=		::devel/argp-standalone
LIB_DEPENDS+=		gcrypt::security/libgcrypt

SEPARATE_BUILD=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
AUTOCONF_VERSION=	2.59
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
FAKE_FLAGS=		localstatedir=${PREFIX}/share/examples/freeipmi \
			sysconfdir=${PREFIX}/share/examples/freeipmi

.if ("${OStype}" == "MirBSD") || ("${OStype}" == "OpenBSD")
.  if "${MACHINE_ARCH}" == "i386"
IOPL_LIBS=		-li386
.  elif "${MACHINE_ARCH}" == "amd64"
IOPL_LIBS=		-lamd64
.  endif
.endif
EXTRA_XAKE_FLAGS+=	IOPL_LIBS=${IOPL_LIBS:Q}

post-install:
	cd ${PREFIX}/share/examples/freeipmi && \
	    mv ${WRKINST}${SYSCONFDIR}/ipmi_monitoring_sensors.conf . && \
	    mv db/freeipmi/bmc-config-template db/freeipmi/ipckey . && \
	    rm -rf init.d logrotate.d sysconfig && \
	    rmdir db/freeipmi db log/freeipmi log
	cd ${PREFIX} && rmdir var/cache/ipmimonitoringsdrcache var/cache var
	rmdir ${WRKINST}/var/log/ipmiconsole

.include <bsd.port.mk>
