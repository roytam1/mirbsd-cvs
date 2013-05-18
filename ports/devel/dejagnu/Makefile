# $MirOS: ports/devel/dejagnu/Makefile,v 1.3 2005/04/11 19:38:08 tg Exp $
# $OpenBSD: Makefile,v 1.21 2003/12/27 23:41:41 jose Exp $

COMMENT=			framework to test programs
DISTNAME=	dejagnu-1.4.4
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_GNU:=dejagnu/}
HOMEPAGE=	http://www.gnu.org/software/dejagnu/
LIB_DEPENDS=	tcl84::lang/tcl/8.4
RUN_DEPENDS=	::lang/expect,no_tk

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-tclinclude="${PREFIX}/include/tcl8.4/generic"
CONFIGURE_ENV+=		ac_cv_path_tclsh=${PREFIX}/bin/tclsh8.4

post-build:
	@cd ${WRKBUILD}/doc && makeinfo --no-split dejagnu.texi

post-install:
	${INSTALL_DATA} ${WRKBUILD}/doc/dejagnu.info ${PREFIX}/info

.include <bsd.port.mk>
