# $MirOS$

.if ${USE_MOTIF:L} == "any" || ${USE_MOTIF:L} == "yes"
FLAVORS+=		openmotif lesstif
.  if ${FLAVOR:Mopenmotif} && ${FLAVOR:Mlesstif}
ERRORS+=		"Choose openmotif or lesstif, not both."
.  elif ${FLAVOR:Mopenmotif}
USE_MOTIF=		openmotif
.  elif ${FLAVOR:Mlesstif}
USE_MOTIF=		lesstif
.  else
# default: no flavour selected, use the one "we like best"
# at the moment, this is lesstif, since openmotif is broken
USE_MOTIF=		lesstif
FLAVOR+=		${USE_MOTIF}
.  endif
.endif

.if ${USE_MOTIF:L} == "lesstif"
LIB_DEPENDS+=		Xm.1::x11/lesstif
.elif ${USE_MOTIF:L} == "openmotif"
ERRORS+=		"Cannot be build because x11/openmotif is broken."
LIB_DEPENDS+=		Xm.2::x11/openmotif
.elif ${USE_MOTIF:L} == "no"
ERRORS+=		"USE_MOTIF=no but motif module invoked?"
.elif ${USE_MOTIF:L} != "transparent"
ERRORS+=		"Unknown USE_MOTIF=${USE_MOTIF:Q} settings."
.endif

MOTIFLIB=		-L${LOCALBASE}/lib -lXm
MAKE_ENV+=		MOTIFLIB=${MOTIFLIB:Q}

.if ${USE_X11:L} != "yes"
ERRORS+=		"USE_X11 is off, ask the port maintainer to fix it."
.endif
