# $MirOS: ports/security/f-prot/Makefile,v 1.2 2005/04/10 21:50:53 tg Exp $

.include <mirports.sys.mk>

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
.if ${OSname} != "openbsd"
EMUL=			openbsd
.endif

COMMENT=		"personal use freeware virus scanner"
CATEGORIES=		security sysutils virus
V=			4.5.3
DISTNAME=		fp-openbsd-ws-${V}
PKGNAME=		f-prot-${V}
HOMEPAGE=		http://www.f-prot.com/
MASTER_SITES=		http://files.f-prot.com/files/bsd-x86/
RESPONSIBLE=		Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

# free for personal use
PERMIT_DISTFILES_CDROM=	"must not distribute"
PERMIT_DISTFILES_FTP=	"must not distribute"
PERMIT_PACKAGE_CDROM=	"must not distribute"
PERMIT_PACKAGE_FTP=	"must not distribute"

WRKDIST=		${WRKDIR}/f-prot
FPDIR=			${PREFIX}/f-prot
DOCDIR=			${PREFIX}/share/doc/f-prot
DATAS=			ENGLISH.TX0 MACRO.DEF SIGN.DEF SIGN2.DEF \
			f-prot-openbsd3.3 f-prot-openbsd3.4
DOCS=			../CHANGES ../LICENSE ../README add_info.html \
			auto_updt.html comm_scan.html index.html \
			inf_eicar.gif info_options.html inst_pro.html \
			loc_files.html macro_scanning_options.html \
			main_feat.html man_updt.html norm_scan.gif \
			per_scan.html reporting_options.html \
			scanning_options.html screenshot.jpg sys_req.html \
			test_eicar.html test_inst.html updater.html \
			updater_req.html updt_macro.gif updt_sign.gif \
			updt_signature.gif

do-build:
	@sed -e 's#@@PREFIX@@#${PREFIX}#g' \
	    <${WRKSRC}/f-prot.sh >${WRKSRC}/f-prot

do-install:
	${INSTALL_SCRIPT} ${WRKSRC}/f-prot ${PREFIX}/bin/
	${INSTALL_DATA_DIR} ${FPDIR} ${DOCDIR}
.for _i in ${DATAS}
	${INSTALL_DATA} ${WRKSRC}/${_i} ${FPDIR}/
.endfor
	${INSTALL_MAN} ${WRKSRC}/man_pages/f-prot.1 \
	    ${PREFIX}/man/man1/
.for _i in ${DOCS}
	${INSTALL_DATA} ${WRKSRC}/doc_ws/${_i} ${DOCDIR}/
.endfor
	chmod 555 ${FPDIR}/f-prot-openbsd3.{3,4}
	${INSTALL_DATA} ${FILESDIR}/KEY.ASC ${DOCDIR}/

.include <bsd.port.mk>
