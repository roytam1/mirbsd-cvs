# $MirOS$

.MAIN: all

all:
	@echo "Not a normal Makefile."

.include <mirports.sys.mk>
.if defined(GNUSYSTEM_AUX_DIR)
.  include "${GNUSYSTEM_AUX_DIR}/locations.mk"
.endif

.if defined(GNU_AUX_CONTRIB_DIR) && !empty(GNU_AUX_CONTRIB_DIR)

IGNORES= \
	texinfo.tex

.  include "${GNU_AUX_CONTRIB_DIR}/gnu/aux/update.mk"

.else
update:
	@echo "Error: GNU_AUX_CONTRIB_DIR not set."
.endif

.PHONY: all update
