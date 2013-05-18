# $OpenBSD: ocaml.port.mk,v 1.4 2004/03/05 21:54:36 avsm Exp $

# regular file usage for bytecode:
# PLIST               -- bytecode base files
# PFRAG.foo           -- bytecode files for FLAVOUR == foo
# PFRAG.no-foo        -- bytecode files for FLAVOUR != foo
# extended file usage for nativecode:
# PFRAG.native        -- nativecode base files
# PFRAG.native.foo    -- nativecode files for FLAVOUR == foo
# PFRAG.native.no-foo -- nativecode files for FLAVOUR != foo

.if ${MACHINE_ARCH} == "alpha" || ${MACHINE_ARCH} == "i386" || \
	${MACHINE_ARCH} == "sparc" || ${MACHINE_ARCH} == "amd64"
MODOCAML_NATIVE=Yes

# include nativecode base files
SED_PLIST+=	|sed -e '/^%%native%%$$/r${PKGDIR}/PFRAG.native' -e '//d'

# create sed substitution for nativecode FLAVOURS
.  if !empty(FLAVOURS)
.    for _i in ${FLAVOURS:L}
.      if empty(FLAVOUR:L:M${_i})
SED_PLIST+=	|sed -e '/^!%%native\.${_i}%%$$/r${PKGDIR}/PFRAG.native.no-${_i}' -e '//d' -e '/^%%native\.${_i}%%$$/d'
.      else
SED_PLIST+=	|sed -e '/^!%%native\.${_i}%%$$/d' -e '/^%%native\.${_i}%%$$/r${PKGDIR}/PFRAG.native.${_i}' -e '//d' 
.      endif
.    endfor
.  endif

.else

MODOCAML_NATIVE=No
RUN_DEPENDS+=	::lang/ocaml

# remove native base file entry from PLIST
SED_PLIST+=	|sed -e '/^%%native%%$$/d'

# remove nativecode FLAVOUR entries from PLIST
.  if !empty(FLAVOURS)
.    for _i in ${FLAVOURS:L}
SED_PLIST+=	|sed -e '/^!%%native\.${_i}%%$$/d' -e '/^%%native\.${_i}%%$$/d'
.    endfor
.  endif
.endif

BUILD_DEPENDS+=	::lang/ocaml
