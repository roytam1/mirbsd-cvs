# $MirOS$

LT_VERSION=		9:10:3
FT_VERSION=		${LT_VERSION:S/:/./g}
LT_CURRENT=		${FT_VERSION:R:R}
LT_REVISION=		${FT_VERSION:R:E}
LT_AGE=			${FT_VERSION:E}
SHLIB_MAJOR!=		print $$((${LT_CURRENT} - ${LT_AGE}))
SHLIB_MINOR=		${LT_AGE}

SUBST_VARS+=		-e 's!@X11BASE@!${X11BASE}!g'
SUBST_VARS+=		-e 's!@ft_version@!${FT_VERSION}!g'

all: freetype-config freetype2.pc

freetype-config: freetype-config.in
	sed ${SUBST_VARS} <$> >$@

freetype2.pc: freetype2.in
	sed ${SUBST_VARS} <$> >$@

