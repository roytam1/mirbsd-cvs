# $MirOS: src/gnu/share/Makefile,v 1.2 2005/02/11 14:34:10 tg Exp $

.MAIN: all

all:
	@echo "Not a normal Makefile."

.include <bsd.own.mk>
.if defined(GNUSYSTEM_AUX_DIR)
.  include "${GNUSYSTEM_AUX_DIR}/locations.mk"
.endif

.if defined(GNU_AUX_CONTRIB_DIR) && !empty(GNU_AUX_CONTRIB_DIR)

IGNORES= \
	texinfo.tex

.  if exists(${GNU_AUX_CONTRIB_DIR}/gnu/aux/update.mk)
.    include "${GNU_AUX_CONTRIB_DIR}/gnu/aux/update.mk"
.  endif

.else
update:
	@echo "Error: GNU_AUX_CONTRIB_DIR not set."
.endif

.PHONY: all update
