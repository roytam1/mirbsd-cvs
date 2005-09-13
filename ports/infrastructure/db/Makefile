# $MirOS: ports/infrastructure/db/Makefile,v 1.2 2005/05/21 00:16:01 tg Exp $

.MAIN: all

all:
	@echo "Not a normal Makefile."

.if defined(SHOW_ONLY) || make(update)
.  include <bsd.own.mk>
.else
.  include <mirports.sys.mk>
.endif
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
