# $MirOS: ports/infrastructure/mk/gnu.port.mk,v 1.60 2015/07/19 12:55:08 tg Exp $
# $OpenBSD: gnu.port.mk,v 1.19 2004/06/06 11:49:08 espie Exp $

AUTOCONF_NEW?=		No
.if ${AUTOCONF_NEW:L} == "yes"
AUTOCONF_VERSION?=	2.61
.else
AUTOCONF_VERSION?=	2.13
.endif
AUTOMAKE_VERSION?=	1.4

MODGNU_RECURSE_DIRS?=	${WRKSRC}
AUTOGEN?=		${SHELL} ${PORTSDIR}/infrastructure/scripts/autogen.sh
MODGNU_COPIES?=		compile config-ml.in config.guess \
			config.libpath config.rpath config.sub depcomp \
			install-sh m4salt.inc m4sugar.inc \
			mdate-sh missing mkinstalldirs move-if-change \
			reloc-ldflags ylwrap ${MODGNU_EXTRA_COPIES}

PATCH_CHECK_ONLY?=	No
MODGNU_configure=	rm -f ${WRKCONF:Q}/config.cache; \
			${MODSIMPLE_configure}; \
			[[ ! -e ${WRKCONF}/config.log ]] || fgrep -A 1 \
			    'previous declaration' ${WRKCONF}/config.log | \
			    fgrep -v -e '$$? = ' -e ': In function ' \
			    ${MODGNU_TYPESCAN:S/^/-e /} || :
REGRESS_TARGET?=	check
AUTOCONF?=		autoconf
AUTOUPDATE?=		autoupdate
AUTOHEADER?=		autoheader
# missing ?= not an oversight
AUTOCONF_ENV=		PATH=${PORTPATH:Q} PORTSDIR=${PORTSDIR:Q} \
			M4=${M4:Q} \
			AUTOCONF_VERSION=${AUTOCONF_VERSION} \
			AUTOMAKE_VERSION=${AUTOMAKE_VERSION}
MAKE_FLAGS+=		V=1 mkdir_p='mkdir -p' \
			mkinstalldirs='mkdir -p' \
			MAKEINFO="makeinfo --no-split"
FAKE_FLAGS+=		V=1 mkdir_p='mkdir -p' \
			mkinstalldirs='mkdir -p' \
			MAKEINFO="makeinfo --no-split"
CONFIGURE_ENV+=		V=1 \
			MAKEINFO="makeinfo --no-split"

MODGNU_AUTOCONF_DEPS=	::devel/metaauto
.if ${AUTOCONF_VERSION} == "2.13"
MODGNU_AUTOCONF_DEPS+=	:autoconf->=2.13-20080405,<2.14:devel/autoconf/2.13
.elif ${AUTOCONF_VERSION} == "2.60"
MODGNU_AUTOCONF_DEPS+=	:autoconf->=2.60-3,<2.61:devel/autoconf/2.60
.elif ${AUTOCONF_VERSION} == "2.61"
MODGNU_AUTOCONF_DEPS+=	:autoconf->=2.61-1,<2.62:devel/autoconf/2.61
.else
MODGNU_AUTOCONF_DEPS+=	:autoconf-${AUTOCONF_VERSION}*:devel/autoconf/${AUTOCONF_VERSION}
.endif
MODGNU_AUTOMAKE_DEPS=	::devel/metaauto
.if ${AUTOMAKE_VERSION} == "1.9"
MODGNU_AUTOMAKE_DEPS+=	:automake->=1.9.6-5,<1.10:devel/automake/1.9
.else
MODGNU_AUTOMAKE_DEPS+=	:automake-${AUTOMAKE_VERSION}*:devel/automake/${AUTOMAKE_VERSION}
.endif

# Dependencies
.if ${CONFIGURE_STYLE:L:Mautogen}
.  if ${CONFIGURE_STYLE:L:Mno-autoheader}
AUTOCONF_ENV+=		NO_AUTOHEADER=yes
.  endif
# the above BEFORE the below line!
CONFIGURE_STYLE+=	autoconf automake no-autoheader
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
CONFIGURE_ENV+=		AUTOCONF_VERSION=${AUTOCONF_VERSION}
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
_DESTPFX=		'$${${DESTDIRNAME}}'
.  else
_DESTPFX=
.  endif
CONFIGURE_ARGS+=	--cache-file=${WRKCONF:Q}/config.cache
CONFIGURE_ARGS+=	--prefix=${_DESTPFX}${PREFIX:Q}
.  if empty(CONFIGURE_STYLE:L:Mold)
CONFIGURE_ARGS+=	--sysconfdir=${_DESTPFX}${SYSCONFDIR:Q}
.  endif
.  if ${AUTOCONF_VERSION:E} > 59
CONFIGURE_ARGS+=	--datarootdir=${_DESTPFX}${PREFIX:Q}/share
.  endif
CONFIGURE_ARGS+=	--datadir=${_DESTPFX}${PREFIX:Q}/share
CONFIGURE_ARGS+=	--infodir=${_DESTPFX}${PREFIX:Q}/info
CONFIGURE_ARGS+=	--mandir=${_DESTPFX}${PREFIX:Q}/man
.  if ${AUTOCONF_VERSION:E} > 59
CONFIGURE_ARGS+=	--localedir=${_DESTPFX}${PREFIX:Q}/share/locale
CONFIGURE_ARGS+=	--docdir=${_DESTPFX}${PREFIX:Q}/share/doc/\$${PACKAGE}
.  endif
CONFIGURE_ARGS+=	--disable-libtool-lock
CONFIGURE_ARGS+=	--disable-dependency-tracking
.  if ${OStype} == "MirBSD"
CONFIGURE_ARGS+=	--with-gnu-ld
.  endif
.endif

# Files
.if ${MODGNU_MIRLIBTOOL:L} == "yes"
MODGNU_COPIES+=		libtool.m4 ltmain.sh
.endif
MODGNU_NUKES=		${MODGNU_COPIES} autom4te.cache libtool ltconfig

# post-patch per-directory loop

# 1. copy over MirGNUTOOLS into target directories, no matter what
_MODGNU_loop=	rm -rf ${MODGNU_NUKES}; ( cd ${PORTSDIR}/infrastructure/db/; \
		${INSTALL} -c -m 555 ${MODGNU_COPIES} $$d/ ); F=configure.ac; \
		test -e $$F || F=configure.in; [ -e $$F ] && ACAUX=$$(grep -a \
		^AC_CONFIG_AUX_DIR\( $$F | sed -e 's/AC_CONFIG_AUX_DIR(\[*//' \
		-e 's/\]*).*$$//'); [[ -n $$ACAUX && -d $$ACAUX/. ]] || \
		ACAUX=.; if [[ . != $$ACAUX ]]; then ( cd $$ACAUX && rm -rf \
		${MODGNU_NUKES} || :); ${INSTALL} -c -m 555 ${MODGNU_COPIES} \
		$$ACAUX/; fi; export ACAUX;

# 2. update Libtool to MirLibtool
.if ${MODGNU_MIRLIBTOOL:L} != "no"
.  if (${AUTOCONF_VERSION} != "2.13") && \
    (${AUTOCONF_VERSION} != "2.59") && \
    (${AUTOCONF_VERSION} != "2.61")
_MODGNU_loop+=	print "Warning: MirLibtool might fail in $$d due to use" \
		    "of autoconf-${AUTOCONF_VERSION}!";
.  endif
_MODGNU_loop+=	print "Updating to MirLibtool in $$d"; touch $$F; \
		${MKSH} ${PORTSDIR}/infrastructure/scripts/u2mirlibtool \
		    ${PATCHORIG} $$ACAUX;
.endif

# 3. execute hooks
_MODGNU_loop+=	${_MODGNU_loop_hooks}

# 4. run the various GNU tools
.if !${CONFIGURE_STYLE:L:Mautogen}
.  if ${CONFIGURE_STYLE:L:Mautoupdate}
_MODGNU_loop+=	echo "Running autoupdate-${AUTOCONF_VERSION} in $$d"; \
		${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOUPDATE};
.  endif
.  if ${CONFIGURE_STYLE:L:Mautoconf}
_MODGNU_loop+=	echo "Running autoconf-${AUTOCONF_VERSION} in $$d"; \
		${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOCONF};
.  endif
.  if ${CONFIGURE_STYLE:L:Mdetectheader}
_MODGNU_loop+=	F=configure.ac; test -e $$F || F=configure.in; if \
		    ! test -e $$F || fgrep -qe AC_CONFIG_HEADERS -e \
		    AM_CONFIG_HEADER $$F; then \
		echo "Running autoheader-${AUTOCONF_VERSION} in $$d"; \
		${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOHEADER}; \
		fi;
.  elif ${CONFIGURE_STYLE:L:Mautoheader}
_MODGNU_loop+=	echo "Running autoheader-${AUTOCONF_VERSION} in $$d"; \
		${_SYSTRACE_CMD} ${SETENV} ${AUTOCONF_ENV} ${AUTOHEADER};
.  endif
.endif

# finally: everything run after patch
.if ${PATCH_CHECK_ONLY:L} != "yes"
MODGNU_post-patch+=	for d in ${MODGNU_RECURSE_DIRS}; do \
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

.if ${MACHINE_OS} == "Interix"
# poll on Interix only works on procfs... so disable its use
CONFIGURE_ENV+=		ac_cv_func_poll=no
CONFIGURE_ENV+=		ac_cv_header_poll_h=no
.elif ${MACHINE_OS} == "BSD"
# reported to be misused by bsiegert@
CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes
# caught by systrace, tries to write to ${LOCALBASE}/lib as check
CONFIGURE_ENV+=		ac_cv_sys_long_file_names=yes
.  if ${OStype} == "MirBSD"
# cannot be used
CONFIGURE_ENV+=		ac_cv_type_long_double=no ac_cv_sizeof_long_double=0
.  endif
.endif

.if defined(LDADD) && !empty(LDADD)
CONFIGURE_ENV+=		LIBS=${LDADD:Q}
.endif

# Mac OSX “Leopard” inlining bug workaround
.if "${OStype}:${OSREV}:${MACHINE_ARCH}" == "Darwin:9.5.0:i386"
CONFIGURE_ENV+=		glib_cv_has__inline=no \
			glib_cv_has__inline__=no \
			glib_cv_hasinline=no
.endif
