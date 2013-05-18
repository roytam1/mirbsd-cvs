# $MirOS: ports/infrastructure/mk/motif.port.mk,v 1.2 2007/05/07 22:54:24 tg Exp $

.if ${USE_MOTIF:L} == "any" || ${USE_MOTIF:L} == "yes"
FLAVOURS+=		openmotif lesstif
.  if ${FLAVOUR:Mopenmotif} && ${FLAVOUR:Mlesstif}
ERRORS+=		"Choose openmotif or lesstif, not both."
.  elif ${FLAVOUR:Mopenmotif}
USE_MOTIF=		openmotif
.  elif ${FLAVOUR:Mlesstif}
USE_MOTIF=		lesstif
.  else
# default: no flavour selected, use the one "we like best"
# at the moment, this is lesstif, since openmotif is broken
USE_MOTIF=		lesstif
FLAVOUR+=		${USE_MOTIF}
.  endif
.endif

.if ${USE_MOTIF:L} == "lesstif"
LIB_DEPENDS+=		Xm.1::x11/lesstif
.elif ${USE_MOTIF:L} == "openmotif"
BROKEN+=		x11/openmotif is broken
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
