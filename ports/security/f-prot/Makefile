# $MirOS: ports/security/f-prot/Makefile,v 1.8 2006/12/23 04:02:26 tg Exp $

.include <mirports.sys.mk>

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
.if ${OSname} != "openbsd"
EMUL=			openbsd
.endif

COMMENT=		personal use freeware virus scanner
CATEGORIES=		security sysutils virus
VERSION=		4.6.2
DASH_VER=		1
DISTNAME=		fp-openbsd-ws-${VERSION}
PKGNAME=		f-prot-${VERSION}-${DASH_VER}
HOMEPAGE=		http://www.f-prot.com/
MASTER_SITES=		http://files.f-prot.com/files/bsd-x86/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# free for personal use
PERMIT_DISTFILES_CDROM=	"must not distribute"
PERMIT_DISTFILES_FTP=	"must not distribute"
PERMIT_PACKAGE_CDROM=	"must not distribute"
PERMIT_PACKAGE_FTP=	"must not distribute"

SUBST_VARS+=		BINOWN
WRKDIST=		${WRKDIR}/f-prot
DOCDIR=			${PREFIX}/share/doc/f-prot
DATAS=			ENGLISH.TX0 MACRO.DEF SIGN.DEF SIGN2.DEF f-prot
DOCS=			../CHANGES ../LICENSE ../LICENSE-FPAV \
			../LICENSES-others ../README add_info.html \
			auto_updt.html comm_scan.html index.html \
			inf_eicar.gif info_options.html inst_pro.html \
			loc_files.html macro_scanning_options.html \
			main_feat.html man_updt.html per_scan.html \
			reporting_options.html scanning_options.html \
			screenshot.jpg sys_req.html test_eicar.html \
			test_inst.html updater.html updater_req.html \
			updt_macro.gif updt_sign.gif updt_signature.gif

NO_BUILD=		Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/f-prot ${DOCDIR}
.for _i in ${DATAS}
	${INSTALL_DATA} ${WRKSRC}/${_i} ${PREFIX}/f-prot/
.endfor
	${INSTALL_MAN} ${WRKSRC}/man_pages/f-prot.1 \
	    ${PREFIX}/man/man1/
.for _i in ${DOCS}
	${INSTALL_DATA} ${WRKSRC}/doc_ws/${_i} ${DOCDIR}/
.endfor
	chmod 555 ${PREFIX}/f-prot/f-prot
	${INSTALL_SCRIPT} ${WRKSRC}/f-prot.sh ${PREFIX}/f-prot/
	ln -sf ${TRUEPREFIX}/f-prot/f-prot.sh ${PREFIX}/bin/f-prot
	${INSTALL_DATA} ${FILESDIR}/KEY.ASC ${DOCDIR}/

.include <bsd.port.mk>
