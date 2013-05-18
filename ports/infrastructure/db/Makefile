# $MirOS: ports/infrastructure/db/Makefile,v 1.3 2005/09/13 10:43:50 tg Exp $

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

IGNORES=

.  include "${GNU_AUX_CONTRIB_DIR}/gnu/aux/update.mk"

.else
update:
	@echo "Error: GNU_AUX_CONTRIB_DIR not set."
.endif

.PHONY: all update
