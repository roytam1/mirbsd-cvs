# $MirOS: ports/infrastructure/mk/gnu.port.mk,v 1.18 2006/02/20 18:57:27 tg Exp $
# $OpenBSD: gnu.port.mk,v 1.19 2004/06/06 11:49:08 espie Exp $

AUTOCONF_NEW?=		No
.if ${AUTOCONF_NEW:L} == "yes"
AUTOCONF_VERSION?=	2.60
.else
AUTOCONF_VERSION?=	2.13
.endif
AUTOMAKE_VERSION?=	1.4

MODGNU_CONFIG_GUESS_DIRS?= ${WRKSRC}
AUTOGEN?=		${SHELL} ${PORTSDIR}/infrastructure/scripts/autogen.sh
MODGNU_COPIES?=		_gplwarn.c compile config-ml.in config.guess \
			config.libpath config.rpath config.sub depcomp \
			install-reloc install-sh m4salt.inc m4sugar.inc \
			mdate-sh missing mkinstalldirs move-if-change \
			reloc-ldflags ylwrap ${MODGNU_EXTRA_COPIES}

PATCH_CHECK_ONLY?=	No
MODGNU_configure=	${MODSIMPLE_configure}
REGRESS_TARGET?=	check
AUTOCONF?=		autoconf
AUTOUPDATE?=		autoupdate
AUTOHEADER?=		autoheader
# missing ?= not an oversight
AUTOCONF_ENV=		PATH=${PORTPATH:Q} PORTSDIR=${PORTSDIR:Q} \
			M4=${M4:Q} \
			AUTOCONF_VERSION=${AUTOCONF_VERSION} \
			AUTOMAKE_VERSION=${AUTOMAKE_VERSION}
EXTRA_XAKE_FLAGS+=	mkdir_p='mkdir -p' \
			MAKEINFO="makeinfo --no-split"
CONFIGURE_ENV+=		MAKEINFO="makeinfo --no-split"

MODGNU_AUTOMAKE_DEPS=	::devel/metaauto ::devel/automake/${AUTOMAKE_VERSION}
MODGNU_AUTOCONF_DEPS=	::devel/metaauto ::devel/autoconf/${AUTOCONF_VERSION}

# Dependencies
.if ${CONFIGURE_STYLE:L:Mautogen}
.  if ${CONFIGURE_STYLE:L:Mno-autoheader}
AUTOCONF_ENV+=		NO_AUTOHEADER=yes
.  endif
# the above BEFORE the below line!
CONFIGURE_STYLE+=	automake no-autoheader
BUILD_DEPENDS+=		${MODGNU_AUTOCONF_DEPS}
.endif
.if ${CONFIGURE_STYLE:L:Mautoupdate}
CONFIGURE_STYLE+=	autoconf
.endif

.if ${CONFIGURE_STYLE:L:Mautomake}
BUILD_DEPENDS+=		${MODGNU_AUTOMAKE_DEPS}
.else
REORDER_DEPENDENCIES+=	${PORTSDIR}/infrastructure/templates/automake.dep
.endif

.if ${CONFIGURE_STYLE:L:Mautoconf}
BUILD_DEPENDS+=		${MODGNU_AUTOCONF_DEPS}
MAKE_ENV+=		AUTOCONF_VERSION=${AUTOCONF_VERSION}
.  if !${CONFIGURE_STYLE:L:Mno-autoheader}
CONFIGURE_STYLE+=	autoheader
.  endif
.endif

# needed stuff
.if ${CONFIGURE_STYLE:L:Mautoconf} || ${CONFIGURE_STYLE:L:Mautogen}
MODGNU_MIRLIBTOOL?=	Yes
.endif
MODGNU_MIRLIBTOOL?=	No

.if ${CONFIGURE_STYLE:L:Mgnu}
.  if ${CONFIGURE_STYLE:L:Mdest}
CONFIGURE_ARGS+=	--prefix='$${${DESTDIRNAME}}${PREFIX}'
.  else
CONFIGURE_ARGS+=	--prefix=${PREFIX:Q}
.  endif
.  if empty(CONFIGURE_STYLE:L:Mold)
.    if ${CONFIGURE_STYLE:L:Mdest}
CONFIGURE_ARGS+=	--sysconfdir='$${${DESTDIRNAME}}${SYSCONFDIR}'
.    else
CONFIGURE_ARGS+=	--sysconfdir=${SYSCONFDIR:Q}
.    endif
.  endif
.endif

# Files
.if ${MODGNU_MIRLIBTOOL:L} == "yes"
MODGNU_COPIES+=		libtool.m4 ltmain.sh
.endif
MODGNU_NUKES=		${MODGNU_COPIES} libtool ltconfig

# post-patch per-directory loop

# 1. copy over MirGNUTOOLS into target directories, no matter what
_MODGNU_loop=	rm -f ${MODGNU_NUKES}; ( cd ${PORTSDIR}/infrastructure/db/; \
		install -c -m 555 ${MODGNU_COPIES} $$d/ ); F=configure.ac; \
		test -e $$F || F=configure.in; test -e $$F && ACAUX=$$(grep \
		^AC_CONFIG_AUX_DIR\( $$F | sed -e 's/AC_CONFIG_AUX_DIR(\[*//' \
		-e 's/\]*).*$$//'); test -z "$$ACAUX" && ACAUX=.; if [ . != \
		"$$ACAUX" ]; then ( cd $$ACAUX && rm -f ${MODGNU_NUKES} ); \
		install -c -m 555 ${MODGNU_COPIES} $$ACAUX/; fi; export ACAUX;

# 2. update Libtool to MirLibtool
.if ${MODGNU_MIRLIBTOOL:L} != "no"
_MODGNU_loop+=	print "Updating to MirLibtool in $$d"; \
		touch $$F; L=aclocal.m4; test -s $$L || L=$$ACAUX/$$L; touch \
		$$L; for LP in $${L}${PATCHORIG} $$L; do test -e $$LP || \
		continue; print "/^\\\# serial [0-9].* AC_PROG_LIBTOOL/ka\n" \
		"'a,\$$g/^ifelse(\\[AC_DISABLE_FAST_INSTALL])/kb\n" \
		"'b,\$$g/^AC_MSG_RESULT(\\[\$$SED])/+1kb\n'a,'bd\nwq" \
		| ed -s $$LP 2>/dev/null || true; print "0a\n" \
		"builtin([include], [libtool.m4])\n.\nwq" | ed -s $$LP; done;
.endif

# 3. execute hooks
_MODGNU_loop+=	${_MODGNU_loop_hooks}

# 4. run the various GNU tools
.if ${CONFIGURE_STYLE:L:Mautoupdate}
_MODGNU_loop+=	echo "Running autoupdate-${AUTOCONF_VERSION} in $$d"; \
		${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOUPDATE};
.endif
.if ${CONFIGURE_STYLE:L:Mautoconf}
_MODGNU_loop+=	echo "Running autoconf-${AUTOCONF_VERSION} in $$d"; \
		${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOCONF};
.endif
.if ${CONFIGURE_STYLE:L:Mautoheader}
_MODGNU_loop+=	echo "Running autoheader-${AUTOCONF_VERSION} in $$d"; \
		${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOHEADER};
.endif

# finally: everything run after patch
.if ${PATCH_CHECK_ONLY:L} != "yes"
MODGNU_post-patch+=	for d in ${MODGNU_CONFIG_GUESS_DIRS}; do \
				( cd $$d; ${_MODGNU_loop} ); done;

# autogen is an exception, it is run only once in the toplevel directory.
# If you need more, use a custom autogen.sh script.
.if ${CONFIGURE_STYLE:L:Mautogen}
MODGNU_post-patch+=	echo "Running autotools regeneration script in ${WRKSRC}"; \
			cd ${WRKSRC}; \
			${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOGEN};
.endif

.endif

# OS-dependent checks

.if ${OStype} == "Interix"
# poll on Interix only works on procfs... so disable its use
CONFIGURE_ENV+=		ac_cv_func_poll=no
CONFIGURE_ENV+=		ac_cv_header_poll_h=no
.endif

.if ${OStype:M*BSD}
# mis-detected on MirBSD, OpenBSD due to proto in <sys/types.h>
# probably an autoconf shortcoming though
CONFIGURE_ENV+=		ac_cv_func_ftruncate=yes
CONFIGURE_ENV+=		ac_cv_func_lseek=yes
CONFIGURE_ENV+=		ac_cv_func_truncate=yes
# reported to be misused by bsiegert@
CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes
.endif

.if defined(LDADD) && !empty(LDADD)
CONFIGURE_ENV+=		LIBS=${LDADD:Q}
.endif
