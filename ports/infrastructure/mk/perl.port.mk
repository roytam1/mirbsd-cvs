# $MirOS: ports/infrastructure/mk/perl.port.mk,v 1.13 2009/08/16 16:27:09 tg Exp $
# $OpenBSD: perl.port.mk,v 1.9 2004/06/08 20:28:19 sturm Exp $
# Based on bsd.port.mk, originally by Jordan K. Hubbard.

.ifndef P5ARCH
.  include "${PORTSDIR}/infrastructure/mk/p5.port.mk"
.endif

MODPERL_BUILD?=	Build

MODPERL_PRE=	${MODPERL_DESTDIR}${PREFIX}
MODPERL_MANPRE=	${MODPERL_PRE}/man/man
MODPERL_SITEPRE=${MODPERL_PRE}/${P5SITE}
MODPERL_SRC?=	${WRKSRC}

MODPERL_CONFIG_VARS+= INSTALLSITELIB=${MODPERL_SITEPRE:Q} \
	INSTALLSITEARCH="\$${INSTALLSITELIB}/${MODPERL_ARCH}" \
	INSTALLPRIVLIB=${MODPERL_DESTDIR}/usr/libdata/perl5 \
	INSTALLARCHLIB="\$${INSTALLPRIVLIB}/${MODPERL_ARCH}" \
	INSTALLBIN=${MODPERL_PRE:Q}/bin INSTALLSCRIPT='$${INSTALLBIN}' \
	INSTALLMAN1DIR=${MODPERL_MANPRE:Q}1 \
	INSTALLSITEMAN1DIR=${MODPERL_MANPRE:Q}1 \
	INSTALLVENDORMAN1DIR=${MODPERL_MANPRE:Q}1 \
	INSTALLMAN3DIR=${MODPERL_MANPRE:Q}3 \
	INSTALLSITEMAN3DIR=${MODPERL_MANPRE:Q}3 \
	INSTALLVENDORMAN3DIR=${MODPERL_MANPRE:Q}3 ${CONFIGURE_ARGS}

.if ${CONFIGURE_STYLE:L:Mmodbuild}
.  if !${PKGNAME:Mp5-Module-Build*}
BUILD_DEPENDS+=	::devel/p5-Module-Build
.  endif
MODPERL_configure= cd ${MODPERL_SRC}; ${_SYSTRACE_CMD} ${SETENV} ${CONFIGURE_ENV} \
	/usr/bin/perl Build.PL install_path=lib=${MODPERL_SITEPRE:Q} \
	install_path=arch=${MODPERL_SITEPRE:Q}/${MODPERL_ARCH:Q} \
	install_path=libdoc=${MODPERL_MANPRE:Q}3 \
	install_path=bindoc=${MODPERL_MANPRE:Q}1 \
	install_path=bin=${MODPERL_PRE:Q}/bin \
	install_path=script=${MODPERL_PRE:Q}/bin ${CONFIGURE_ARGS} 
REGRESS_TARGET?=test
.elif ${CONFIGURE_STYLE:L:Mperl}
MODPERL_configure= cd ${MODPERL_SRC}; ${_SYSTRACE_CMD} ${SETENV} ${CONFIGURE_ENV} \
	CC=${_PASS_CC:T:Q} CFLAGS=${CFLAGS:M*:Q} CXX=${_PASS_CXX:T:Q} \
	CXXFLAGS=${CXXFLAGS:M*:Q} YACC=${YACC:Q} LD=${LD:Q} \
	LDFLAGS=${LDFLAGS:Q} /usr/bin/perl Makefile.PL \
	PREFIX=${PREFIX:Q} ${MODPERL_CONFIG_VARS}
REGRESS_TARGET?=test
.endif

MODPERL_pre-fake= \
	${SUDO} mkdir -p ${WRKINST}$$(/usr/bin/perl -e \
	    'use Config; print $$Config{installarchlib}, "\n";')

MODPERL_post-fake= \
	${SUDO} find ${DESTDIR}${PREFIX}/${P5ARCH} -name .packlist -exec rm \{\} \; ; \
	${SUDO} find -d ${DESTDIR}${PREFIX}/${P5ARCH} -type d -exec rmdir \{\} \; 2>&1

.if ${CONFIGURE_STYLE:L:Mmodbuild}
.  if !target(do-build)
do-build: 
	@cd ${MODPERL_SRC} && ${SETENV} ${MAKE_ENV} /usr/bin/perl \
		${MODPERL_BUILD} build
.  endif
.  if !target(do-regress)
do-regress:
	@cd ${MODPERL_SRC} && ${SETENV} ${MAKE_ENV} /usr/bin/perl \
		${MODPERL_BUILD} ${REGRESS_TARGET}

.  endif
.  if !target(do-install)
do-install:
	@cd ${MODPERL_SRC} && ${SETENV} ${MAKE_ENV} /usr/bin/perl \
		${MODPERL_BUILD} destdir=${WRKINST} ${FAKE_TARGET}
.  endif
.endif
