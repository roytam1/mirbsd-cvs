# $MirOS: ports/security/nessus/Makefile,v 1.3 2005/07/07 21:25:54 bsiegert Exp $
# $OpenBSD: Makefile,v 1.35 2004/04/08 16:32:39 sturm Exp $

IGNORE=		"might be broken, used to use Libtool"

COMMENT=			network security scanner
PKGNAME=	nessus-${VERS}-0
CATEGORIES=	security
VERS=		2.0.10a
DIST_SUBDIR=	nessus

DISTFILES=	nessus-libraries-${VERS}${EXTRACT_SUFX} \
		libnasl-${VERS}${EXTRACT_SUFX} \
		nessus-core-${VERS}${EXTRACT_SUFX} \
		nessus-plugins-${VERS}${EXTRACT_SUFX}

NESSUS_DIRS=	${DISTFILES:S/-${VERS}${EXTRACT_SUFX}//g}

MASTER_SITES=	ftp://ftp.nessus.org/pub/nessus/nessus-${VERS}/src/ \
		ftp://mirror.arc.nasa.gov/pub/tools/nessus/nessus-${VERS}/src/ \
		ftp://ftp.gwdg.de/pub/linux/misc/nessus/nessus-${VERS}/src/ \
		ftp://nessus.via.ecp.fr/nessus/nessus-${VERS}/src/ \
		ftp://sunsite.cnlab-switch.ch/mirror/nessus/nessus-${VERS}/src/ \
		ftp://ftp.chg.ru/pub/security/nessus/nessus-${VERS}/src/ \
		ftp://ftp.sekure.net/pub/nessus/nessus-${VERS}/src/ \
		ftp://ftp.nectec.or.th/pub/mirrors/nessus/nessus-${VERS}/src/ \
		ftp://ftp.pt.nessus.org/pub/nessus/nessus-${VERS}/src/ \
		ftp://ftp.au.nessus.org/pub/nessus/nessus-${VERS}/src/ \
		ftp://ftp.stuff.ca/pub/nessus/nessus-${VERS}/src/src/ \
		ftp://ftp.at.nessus.org/pub/nessus/nessus-${VERS}/src/ \
		ftp://ftp.linux.org.tr/pub/nessus/nessus-${VERS}/src/ \
		ftp://cvs.nessus.org/pub/nessus/nessus-${VERS}/src/

HOMEPAGE=	http://www.nessus.org/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=no_x11
FLAVOR?=

# Can't do CONFIGURE_STYLE=autoconf because of configure wrapper
# that builds each tarball in succession.
CONFIGURE_STYLE=gnu
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/nessus-core \
    ${WRKSRC}/nessus-plugins ${WRKSRC}/libnasl ${WRKSRC}/nessus-libraries
CONFIGURE_ARGS+=--localstatedir=/var --disable-nessuspcap \
		--sharedstatedir=/var --enable-shared --enable-bpf-sharing

LIB_DEPENDS=	net::net/libnet
BUILD_DEPENDS=	::devel/bison

.if empty(FLAVOR:L:Mno_x11)
LIB_DEPENDS+=	gtk.1.2,gdk.1.2::x11/gtk+1
USE_X11=	Yes
.else
CONFIGURE_ARGS+=--disable-gtk
.endif

post-extract:
	@sed 's%@@NESSUS_DIRS@@%${NESSUS_DIRS}%g' \
		${FILESDIR}/Makefile > ${WRKSRC}Makefile
	@sed -e 's%@@NESSUS_DIRS@@%${NESSUS_DIRS}%g' \
		-e 's%@@WRKSRC@@%${WRKSRC}%g' \
		${FILESDIR}/configure > ${WRKSRC}configure
	@sed -e 's%@@WRKSRC@@%${WRKSRC}%g' -e 's%@@VERS@@%${VERS}%g' \
		-e 's%@@PREFIX@@%${PREFIX}%g' \
		${FILESDIR}/nessus-config > ${WRKSRC}nessus-config
	@sed 's%@@WRKSRC@@%${WRKSRC}%g' \
		${FILESDIR}/nasl-config > ${WRKSRC}nasl-config
	@${CHMOD} 755 ${WRKSRC}*
	@cd ${WRKSRC}nessus-libraries/include ; ln -s . nessus
	@cd ${WRKSRC}libnasl/include ; ln -s . nessus

NO_REGRESS=	Yes

post-install:
	@${STRIP} ${PREFIX}/bin/{nasl,nessus,nessus-mkrand} ${PREFIX}/sbin/nessusd

.include <bsd.port.mk>
