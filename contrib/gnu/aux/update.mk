# $MirOS: contrib/gnu/aux/update.mk,v 1.3 2005/02/11 14:31:17 tg Exp $

ONLY?=
SOURCES=
WARNS=
IGNORED=
IGNORES?=

PIDBDIR=	$${PORTSDIR:-/usr/ports}${.CURDIR:S/${PORTSDIR}//}

# available sources:
#	automake/lib/py-compile
#	automake/lib/symlink-tree

# need fixes:
#	gettext/gettext-runtime/m4/gettext.m4
#	gettext/autoconf-lib-link/m4/lib-ld.m4
#	gettext/autoconf-lib-link/m4/lib-link.m4
#	gettext/autoconf-lib-link/m4/lib-prefix.m4
# removed:
#	libtool/libtoolize


POSSIBLE_SOURCES+=					\
	automake/lib/compile				\
	automake/lib/config-ml.in			\
	automake/lib/depcomp				\
	automake/lib/mdate-sh				\
	automake/lib/missing				\
	automake/lib/texinfo.tex			\
	automake/lib/ylwrap				\
	aux/install-sh					\
	aux/mkinstalldirs				\
	aux/move-if-change				\
	config/config.guess				\
	config/config.sub				\
	gettext/autoconf-lib-link/config.rpath		\
	gettext/config/config.libpath			\
	gettext/config/install-reloc			\
	gettext/config/reloc-ldflags			\
	libtool/libtool.m4				\
	libtool/ltmain.sh				\
	libtool/m4salt.inc				\
	libtool/m4sugar.inc

.if !empty(ONLY)
POSSIBLE_SOURCES=${ONLY}
.endif

.for _i in ${POSSIBLE_SOURCES}
.  if !empty(IGNORES:M${_i:T})
IGNORED+= ${GNU_AUX_CONTRIB_DIR}/gnu/${_i}
.  elif exists(${GNU_AUX_CONTRIB_DIR}/gnu/${_i})
SOURCES+= ${GNU_AUX_CONTRIB_DIR}/gnu/${_i}
.  else
WARNS+=   ${GNU_AUX_CONTRIB_DIR}/gnu/${_i}
.  endif
.endfor

update:
.if !empty(SOURCES)
	cd ${.CURDIR}; \
	for srcf in ${SOURCES}; do \
		dstf="$$(basename $$srcf)"; \
		echo -n "$$dstf	<== $$srcf processing... "; \
		printf '/\\$$%s\n%s\n%s\nwq %s\n' \
		    "MirOS:/ka" "'a,t'a-1" \
		    "'as~\\\$$MirOS~_MirOS~" \
		    $$dstf | ed -s "$$srcf"; \
		echo "done"; \
	done
.else
	@echo "Warning: SOURCES are empty."
.endif
.if !empty(WARNS)
	@echo "============================================================"
	@echo "The following files could not be found:"
.  for _i in ${WARNS}
	@echo '| ${_i}'
.  endfor
	@echo "============================================================"
.endif
# No libtoolize ATM, see above
#	if test -s ${.CURDIR}/libtoolize; then \
#		printf '%s\nwq\n' '1,$$g#@pkgdatadir@#s##${PIDBDIR}#' \
#		    | ed -s ${.CURDIR}/libtoolize; \
#	else \
#		true; \
#	fi
.if !empty(IGNORED)
	@echo "============================================================"
	@echo "The following files have been ignored:"
.  for _i in ${IGNORED}
	@echo '| ${_i}'
.  endfor
	@echo "============================================================"
.endif
