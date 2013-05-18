# $MirOS: ports/devel/cvsweb/Makefile,v 1.2 2005/09/11 02:33:50 tg Exp $
# $OpenBSD: Makefile,v 1.30 2004/02/01 19:47:27 naddy Exp $
# $FreeBSD: ports/devel/cvsweb/Makefile,v 1.28 2000/09/23 20:48:45 knu Exp $

COMMENT=			WWW CGI script to browse CVS repository trees
DISTNAME=	cvsweb-3.0.5
CATEGORIES=	devel www
HOMEPAGE=	http://www.freebsd.org/projects/cvsweb.html

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_FREEBSD_LOCAL:=scop/} \
		http://people.FreeBSD.org/~scop/cvsweb/

NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*

RUN_DEPENDS=	::devel/p5-IPC-Run \
		::www/p5-URI

PREFIX=		${WWW_PREFIX}
CONFDIR=	${PREFIX}/conf

CONFFILES=	cvsweb.conf cvsweb.conf-freebsd cvsweb.conf-netbsd \
		cvsweb.conf-openbsd cvsweb.conf-ruby
ICONS=		back.gif binary.gif dir.gif miniback.gif minidir.gif \
		minigraph.png minitext.gif text.gif
CSS=		cvsweb.css
ENSCRIPT=	lang_cvsweb.st lang_cvsweb_diff.st
SAMPLES=	cvsweb-httpd.conf

SUBST_VARS=	CONFDIR WWW_PREFIX

do-configure:
	print '1,$$g@%%CONFDIR%%@s@@${CONFDIR}@g\nwq' \
	    | ed -s ${WRKSRC}/cvsweb.cgi

do-install:
	${INSTALL_SCRIPT_DIR} ${PREFIX}/cgi-bin
	${INSTALL_SCRIPT} ${WRKSRC}/cvsweb.cgi ${PREFIX}/cgi-bin/
	${INSTALL_DATA_DIR} ${CONFDIR}/cvsweb
.for file in ${CONFFILES}
	${INSTALL_DATA} ${WRKSRC}/${file} ${CONFDIR}/cvsweb/${file}.dist
.endfor
	${INSTALL_DATA} ${FILESDIR}/README.chroot ${CONFDIR}/cvsweb/
.for file in ${SAMPLES}
	${INSTALL_DATA} ${WRKSRC}/samples/${file} ${CONFDIR}/cvsweb/
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/icons/cvsweb
.for file in ${ICONS}
	${INSTALL_DATA} ${WRKSRC}/icons/${file} ${PREFIX}/icons/cvsweb/${file}
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/css
.for file in ${CSS}
	${INSTALL_DATA} ${WRKSRC}/css/${file} ${PREFIX}/css/${file}.dist
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/enscript
.for file in ${ENSCRIPT}
	${INSTALL_DATA} ${WRKSRC}/enscript/${file} ${PREFIX}/enscript/
.endfor

.include <bsd.port.mk>
