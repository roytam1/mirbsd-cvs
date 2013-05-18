# $MirOS: ports/infrastructure/mk/perl.port.mk,v 1.6 2005/12/28 16:35:36 tg Exp $
# $OpenBSD: perl.port.mk,v 1.9 2004/06/08 20:28:19 sturm Exp $
# Based on bsd.port.mk, originally by Jordan K. Hubbard.

REGRESS_TARGET?=test
MODPERL_BUILD?=	Build
MODPERL_ARCH!=	/usr/bin/perl -e 'use Config; print $$Config{archname}, "\n";'

MODPERL_PRE=	${MODPERL_DESTDIR}${PREFIX}
MODPERL_MANPRE=	${MODPERL_PRE}/man/man
MODPERL_SITEPRE=${MODPERL_PRE}/${P5SITE}
MODPERL_SRC?=	${WRKSRC}

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
.else
MODPERL_configure= cd ${MODPERL_SRC}; ${_SYSTRACE_CMD} ${SETENV} ${CONFIGURE_ENV} \
	CC=${CC:Q} CFLAGS=${CFLAGS:M*:Q} CXX=${CXX:Q} \
	CXXFLAGS=${CXXFLAGS:M*:Q} YACC=${YACC:Q} LD=${LD:Q} \
	LDFLAGS=${LDFLAGS:Q} /usr/bin/perl Makefile.PL \
     	PREFIX=${PREFIX:Q} INSTALLSITELIB=${MODPERL_SITEPRE:Q} \
	INSTALLSITEARCH="\$${INSTALLSITELIB}/${MODPERL_ARCH}" \
	INSTALLPRIVLIB=${MODPERL_DESTDIR:Q}/usr/libdata/perl5 \
	INSTALLARCHLIB="\$${INSTALLPRIVLIB}/${MODPERL_ARCH}" \
	INSTALLBIN=${MODPERL_PRE:Q}/bin INSTALLSCRIPT='$${INSTALLBIN}' \
	INSTALLMAN1DIR=${MODPERL_MANPRE:Q}1 \
	INSTALLSITEMAN1DIR=${MODPERL_MANPRE:Q}1 \
	INSTALLVENDORMAN1DIR=${MODPERL_MANPRE:Q}1 \
	INSTALLMAN3DIR=${MODPERL_MANPRE:Q}3 \
	INSTALLSITEMAN3DIR=${MODPERL_MANPRE:Q}3 \
	INSTALLVENDORMAN3DIR=${MODPERL_MANPRE:Q}3 ${CONFIGURE_ARGS}
.endif

MODPERL_pre_fake= \
	${SUDO} mkdir -p ${WRKINST}$$(/usr/bin/perl -e \
	    'use Config; print $$Config{installarchlib}, "\n";')

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

P5MAN3EXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{man3ext};'
P5DLEXT!=	/usr/bin/perl -e 'use Config; print ".".$$Config{dlext};'

SUBST_VARS+=	P5ARCH P5SITE P5MAN3EXT P5DLEXT
