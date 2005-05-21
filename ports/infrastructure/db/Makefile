# $MirOS: ports/infrastructure/db/Makefile,v 1.1.7.1 2005/03/18 15:47:16 tg Exp $

.MAIN: all

all:
	@echo "Not a normal Makefile."

.if defined(SHOW_ONLY)
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
