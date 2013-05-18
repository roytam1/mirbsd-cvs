# $MirOS: ports/devel/apr/Makefile.inc,v 1.4 2008/10/02 18:54:48 bsiegert Exp $

VERSION?=		0.9.18
CATEGORIES=		devel net

HOMEPAGE=		http://apr.apache.org/
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# Apache Licence
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://mirror.serversupportforum.de/apache/apr/ \
			http://apache.autinity.de/apr/ \
			http://www.ftp.apache.mirroarrr.de/apr/ \
			http://apache.mirroring.de/apr/ \
			http://apache.linux-mirror.org/apr/ \
			http://apache.easy-webs.de/apr/ \
			http://ftp.hosting-studio.de/pub/linux/apache/apr/ \
			http://www.artfiles.org/apache.org/apr/ \
			http://www.apache.de/dist/apr/ \
			http://apache.speedbone.de/apr/ \
			http://mirrorspace.org/apache/apr/ \
			http://netmirror.org/mirror/apache.org/apr/ \
			http://apache.imsam.info/apr/ \
			http://apache.dns4.com/apr/ \
			http://ftp.uni-erlangen.de/pub/mirrors/apache/apr/ \
			http://ftp.plusline.de/ftp.apache.org/apr/ \
			http://apache.ntspace.net/apr/ \
			ftp://ftp.uni-erlangen.de/pub/mirrors/apache/apr/ \
			ftp://ftp.apache.de/mirrors/dev.apache.org/dist/apr/ \
			ftp://ftp.fu-berlin.de/unix/www/apache/apr/ \
			ftp://ftp-stud.fht-esslingen.de/pub/Mirrors/ftp.apache.org/dist/apr/ \
			ftp://ftp.plusline.de/pub/ftp.apache.org/apr/ \
			http://www.apache.org/dist/apr/ \
			http://www.eu.apache.org/dist/apr/
EXTRACT_SUFX=		.tar.bz2

#LIB_DEPENDS+=		xml2::textproc/libxml
#LIB_DEPENDS+=		neon::net/neon
#RUN_DEPENDS+=		:p5-URI-*:www/p5-URI
#MODULES=		textproc/expat

CONFIGURE_STYLE?=	autoconf
AUTOCONF_NEW=		Yes

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
